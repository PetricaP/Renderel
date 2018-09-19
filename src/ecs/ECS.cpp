#include "ecs/ECS.hpp"
#include "math/Math.hpp"
#include <cstring>
#include <iostream>

namespace renderel {

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

EntityHandle ECS::MakeEntity(BaseECSComponent entityComponents[],
							 const unsigned int entityComponentIDs[],
							 size_t numComponents) {
	EntityData *entityData = new EntityData;

	EntityHandle handle = static_cast<EntityHandle>(&entityData->entity);
	/* Create every component and attach it to the entity */
	for (unsigned int i = 0; i < numComponents; ++i) {

		unsigned int id = entityComponentIDs[i];
		if (!BaseECSComponent::IsTypeValid(id)) {
			std::cerr << "ECS: [Error] %u is not a valid component type.\n";
			delete entityData;
			return NULL_ENTITY_HANDLE;
		}

		AddComponentInternal(handle, entityData->entity, id,
							 &entityComponents[i]);
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
						componentData.indexInComponentArray);
	}

	/* Replace the deleted entity with the entity at the end of the array */
	unsigned int destIndex = HandleToEntityIndex(handle);
	unsigned int srcIndex = static_cast<unsigned int>(m_Entities.size()) - 1;

	delete m_Entities[destIndex];

	m_Entities[destIndex] = m_Entities[srcIndex];
	m_Entities.pop_back();
}

void ECS::AddComponentInternal(EntityHandle handle, Entity &entity,
							   unsigned int id, BaseECSComponent *component) {
	ECSComponentCreateFunction createFunction =
		BaseECSComponent::GetTypeCreateFunction(id);

	ComponentData componentData;

	componentData.componentType = id;

	componentData.indexInComponentArray = createFunction(
		m_Components[id], handle, component, BaseECSComponent::GetTypeSize(id));

	entity.push_back(componentData);
}

void ECS::DeleteComponent(unsigned int componentID, unsigned int index) {

	/* Get the block of memory in which the component is located */
	std::vector<byte> &memory = m_Components[componentID];

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
			srcIndex == component.indexInComponentArray) {

			component.indexInComponentArray = index;
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
			DeleteComponent(componentID, entity[i].indexInComponentArray);

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
											std::vector<byte> &memory,
											unsigned int componentID) {
	for (const auto &component : entity) {
		if (componentID == component.componentType) {
			return reinterpret_cast<BaseECSComponent *>(
				&memory[component.indexInComponentArray]);
		}
	}
	return nullptr;
}

bool ECS::RemoveSystem(BaseECSSystem &system) {
	for (unsigned int i = 0; i < m_Systems.size(); ++i) {
		if (&system == m_Systems[i]) {
			m_Systems.erase(m_Systems.begin() + i);
			return true;
		}
	}
	return false;
}

/* No idea what's going on really */
void ECS::UpdateSystems(float deltaTime) {

	std::vector<BaseECSComponent *> componentParam;
	std::vector<std::vector<byte> *> componentArrays;

	for (unsigned int i = 0; i < m_Systems.size(); ++i) {
		const std::vector<unsigned int> &componentTypes =
			m_Systems[i]->GetComponentTypes();
		/* If there is only one component */
		if (componentTypes.size() == 1) {

			unsigned int id = componentTypes[0];
			size_t typeSize = BaseECSComponent::GetTypeSize(id);
			std::vector<byte> &memory = m_Components[id];

			for (unsigned int j = 0; j < memory.size(); j += typeSize) {

				BaseECSComponent *component =
					reinterpret_cast<BaseECSComponent *>(memory[j]);

				m_Systems[i]->UpdateComponents(deltaTime, &component);
			}
		} else {
			UpdateSystemWithMultipleComponents(i, deltaTime, componentTypes,
											   componentParam, componentArrays);
		}
	}
}

void ECS::UpdateSystemWithMultipleComponents(
	unsigned int index, float deltaTime,
	const std::vector<unsigned int> &componentTypes,
	std::vector<BaseECSComponent *> &componentParam,
	std::vector<std::vector<byte> *> &componentArrays) {

	componentParam.resize(
		math::max(componentParam.size(), componentTypes.size()));

	componentArrays.resize(
		math::max(componentArrays.size(), componentTypes.size()));

	for (unsigned int i = 0; i < componentArrays.size(); ++i) {
		componentArrays[i] = &m_Components[componentTypes[i]];
	}

	unsigned int id = componentTypes[0];
	size_t typeSize = BaseECSComponent::GetTypeSize(id);

	for (unsigned int i = 0; i < (*componentArrays[0]).size(); i += typeSize) {

		BaseECSComponent *component =
			reinterpret_cast<BaseECSComponent *>(&componentArrays[0][i]);

		componentParam[0] = component;

		Entity &entity = HandleToEntity(component->entityHandle);

		bool isValid = true;
		for (unsigned int j = 0; j < componentTypes.size(); ++j) {
			if (j == 0) {
				continue;
			}
			componentParam[j] = GetComponentInternal(
				entity, *(componentArrays[j]), componentTypes[j]);

			if (componentParam[j] == nullptr) {
				isValid = false;
				break;
			}
		}

		if (isValid) {
			m_Systems[index]->UpdateComponents(deltaTime, &componentParam[0]);
		}
	}
}

} // namespace renderel
