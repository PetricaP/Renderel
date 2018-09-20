#include "ecs/ECS.hpp"
#include "math/Math.hpp"
#include <cstring>
#include <iostream>

namespace renderel {

/* Defaulted to nullptr */
BaseECSComponent **ECS::tempComponents;
unsigned int *ECS::tempComponentIDs;
int ECS::index = 0;

ECS::~ECS() {
	for (auto &component : m_Components) {
		/* id is the key in the components map */
		unsigned int id = component.first;
		size_t typeSize = BaseECSComponent::GetTypeSize(id);
		ECSComponentFreeFunction freeFunction =
			BaseECSComponent::GetTypeFreeFunction(id);
		/* The block of memory containing all the components of this type */
		ComponentMemory &memory = component.second;
		for (unsigned int i = 0; i < memory.size(); i += typeSize) {
			/* Delete that memory as though it was a BaseECSComponent */
			freeFunction(reinterpret_cast<BaseECSComponent *>(&memory[i]));
		}
	}

	for (auto &entity : m_Entities) {
		delete entity;
	}
}

EntityHandle ECS::MakeEntity(BaseECSComponent **entityComponents,
							 const unsigned int *entityComponentIDs,
							 size_t numComponents) {
	EntityData *entityData = new EntityData;

	EntityHandle handle = static_cast<EntityHandle>(entityData);
	/* Create every component and attach it to the entity */
	for (unsigned int i = 0; i < numComponents; ++i) {

		unsigned int id = entityComponentIDs[i];
		if (!BaseECSComponent::IsTypeValid(id)) {
			std::cerr << "ECS: [Error] %u is not a valid component type.\n";
			delete entityData;
			return NULL_ENTITY_HANDLE;
		}

		AddComponentInternal(handle, entityData->entity, id,
							 entityComponents[i]);
	}

	/* The entity is placed in the last cell of the entity array
	 * and uses that cell's index as its id. */
	entityData->indexInEntityArray =
		static_cast<unsigned int>(m_Entities.size());

	m_Entities.push_back(entityData);

	return handle;
}

void ECS::RemoveEntity(EntityHandle handle) {
	Entity entity = HandleToEntity(handle);
	for (const auto componentData : entity) {
		DeleteComponent(componentData.componentType,
						componentData.keyInComponentMap);
	}

	/* Replace the deleted entity with the entity at the end of the array */
	unsigned int destIndex = HandleToEntityIndex(handle);
	unsigned int srcIndex = static_cast<unsigned int>(m_Entities.size()) - 1;

	delete m_Entities[destIndex];

	m_Entities[destIndex] = m_Entities[srcIndex];
	m_Entities[destIndex]->indexInEntityArray = destIndex;

	m_Entities.pop_back();
}

void ECS::AddComponentInternal(EntityHandle handle, Entity &entity,
							   unsigned int id, BaseECSComponent *component) {
	ECSComponentCreateFunction createFunction =
		BaseECSComponent::GetTypeCreateFunction(id);

	ComponentData componentData;

	componentData.componentType = id;

	componentData.keyInComponentMap =
		createFunction(m_Components[id], handle, component);

	entity.push_back(componentData);
}

void ECS::DeleteComponent(unsigned int componentID, unsigned int index) {

	/* Get the block of memory in which the component is located */
	ComponentMemory &memory = m_Components[componentID];

	ECSComponentFreeFunction freeFunction =
		BaseECSComponent::GetTypeFreeFunction(componentID);

	size_t typeSize = BaseECSComponent::GetTypeSize(componentID);

	/* Figure out where we is the last valid component that should replace
	 * the deleted component and swap them */
	unsigned int srcIndex = static_cast<unsigned int>(memory.size() - typeSize);

	BaseECSComponent *srcComponent =
		reinterpret_cast<BaseECSComponent *>(&memory[srcIndex]);

	BaseECSComponent *destComponent =
		reinterpret_cast<BaseECSComponent *>(&memory[index]);

	freeFunction(destComponent);

	if (index == srcIndex) {
		memory.resize(srcIndex);
		return;
	}

	memcpy(destComponent, srcComponent, typeSize);

	/* Update the info in the entity containing the component */
	Entity &srcEntity = HandleToEntity(srcComponent->entityHandle);
	for (auto &component : srcEntity) {
		if (componentID == component.componentType &&
			srcIndex == component.keyInComponentMap) {

			component.keyInComponentMap = index;
			break;
		}
	}

	memory.resize(srcIndex);
}

bool ECS::RemoveComponentInternal(EntityHandle handle,
								  unsigned int componentID) {
	Entity &entity = HandleToEntity(handle);
	for (unsigned int i = 0; i < entity.size(); ++i) {
		if (componentID == entity[i].componentType) {
			DeleteComponent(componentID, entity[i].keyInComponentMap);

			unsigned int srcIndex =
				static_cast<unsigned int>(entity.size()) - 1;
			unsigned int destIndex = i;

			entity[destIndex] = entity[srcIndex];
			entity.pop_back();

			return true;
		}
	}
	return false;
}

BaseECSComponent *ECS::GetComponentInternal(Entity &entity,
											ComponentMemory &memory,
											unsigned int componentID) {
	for (auto &component : entity) {
		if (componentID == component.componentType) {
			BaseECSComponent *found = reinterpret_cast<BaseECSComponent *>(
				&memory[component.keyInComponentMap]);
			return found;
		}
	}
	return nullptr;
}

/* No idea what's going on really */
void ECS::UpdateSystems(ECSSystemList &ecsSystemList, float deltaTime) {

	std::vector<BaseECSComponent *> componentParam;
	std::vector<ComponentMemory *> componentArrays;

	for (unsigned int i = 0; i < ecsSystemList.size(); ++i) {
		const std::vector<unsigned int> &componentTypes =
			ecsSystemList[i]->GetComponentTypes();
		/* If there is only one component */
		if (componentTypes.size() == 1) {

			/* Get it's type */
			unsigned int id = componentTypes[0];
			size_t typeSize = BaseECSComponent::GetTypeSize(id);

			/* The location in memory of the components of this type*/
			ComponentMemory &memory = m_Components[id];

			/* Go through every component in the array */
			for (unsigned int j = 0; j < memory.size(); j += typeSize) {

				/* Get the component at index j and update it */
				BaseECSComponent *component =
					reinterpret_cast<BaseECSComponent *>(memory[j]);

				ecsSystemList[i]->UpdateComponents(deltaTime, &component);
			}
		} else {
			/* There are more */
			UpdateSystemWithMultipleComponents(i, ecsSystemList, deltaTime,
											   componentTypes, componentParam,
											   componentArrays);
		}
	}
}

/* Component types are the types of the components from the system
 * Component params is just a location for all the components in a system
 * just so we don't need to reallocate this for every system we update */
void ECS::UpdateSystemWithMultipleComponents(
	unsigned int index, ECSSystemList &ecsSystemList, float deltaTime,
	const std::vector<unsigned int> &componentTypes,
	std::vector<BaseECSComponent *> &componentParam,
	std::vector<ComponentMemory *> &componentArrays) {

	const std::vector<unsigned int> &componentFlags =
		ecsSystemList[index]->GetComponentFlags();

	/* Make sure these arrays are big enough for holding all of our component
	 * data */

	componentParam.resize(
		math::max(componentParam.size(), componentTypes.size()));

	componentArrays.resize(
		math::max(componentArrays.size(), componentTypes.size()));

	for (unsigned int i = 0; i < componentArrays.size(); ++i) {
		componentArrays[i] = &m_Components[componentTypes[i]];
	}

	unsigned int id = componentTypes[0];
	unsigned int minCountIndex =
		FindLeastCommonComponent(componentTypes, componentFlags);

	size_t typeSize = BaseECSComponent::GetTypeSize(id);
	ComponentMemory &memory = *componentArrays[minCountIndex];

	/* Look for all the entities that have this component and check if
	 * it also has the other components the system needs */
	for (unsigned int i = 0; i < memory.size(); i += typeSize) {

		BaseECSComponent *component =
			reinterpret_cast<BaseECSComponent *>(&memory[i]);

		componentParam[minCountIndex] = component;

		Entity &entity = HandleToEntity(component->entityHandle);

		/* If an entity doesn't have all the components we need,
		 * don't update it */
		bool isValid = true;
		for (unsigned int j = 0; j < componentTypes.size(); ++j) {
			if (j == minCountIndex) {
				continue;
			}
			componentParam[j] = GetComponentInternal(
				entity, *(componentArrays[j]), componentTypes[j]);

			if (componentParam[j] == nullptr &&
				(componentFlags[j] & BaseECSSystem::FLAG_OPTIONAL) == 0) {
				isValid = false;
				break;
			}
		}

		/* We found an entity that has our component and also has some more */
		if (isValid) {
			ecsSystemList[index]->UpdateComponents(
				deltaTime, &componentParam[minCountIndex]);
		}
	}
}

/* This is so if we only have 2 components of one of the types the system needs,
 * and 10000 of another type, we only check 2 entities */
unsigned int
ECS::FindLeastCommonComponent(const std::vector<unsigned int> &componentTypes,
							  const std::vector<unsigned int> &componentFlags) {

	/* The number of components of the m_Components[0] type */
	unsigned int minCount = static_cast<unsigned int>(-1);

	unsigned int minIndex = 0;

	for (unsigned int i = 0; i < componentTypes.size(); ++i) {
		if ((componentFlags[i] & BaseECSSystem::FLAG_OPTIONAL) != 0) {
			continue;
		}
		size_t typeSize = BaseECSComponent::GetTypeSize(componentTypes[i]);
		/* The number of components of that type */
		unsigned int count =
			static_cast<unsigned int>(m_Components[i].size()) / typeSize;
		if (count <= minCount) {
			minCount = count;
			minIndex = i;
		}
	}

	return minIndex;
}

} // namespace renderel
