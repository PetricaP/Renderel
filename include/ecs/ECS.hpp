#ifndef ECS_HPP
#define ECS_HPP

#include "ECSComponent.hpp"
#include "ECSSystem.hpp"
#include <unordered_map>

namespace renderel {

/* A component is generic so it's just an array of memory */
using ComponentMemory = std::vector<byte>;

/* We will use this ComponentData struct to easily refer
 * to any component an entity might have and manipulate it
 * the way we want */
struct ComponentData {
	/* The id of a component is it's type */
	unsigned int componentType;
	unsigned int indexInComponentArray;
};

/* All an entity is, is just a group of components */
using Entity = std::vector<ComponentData>;

struct EntityData {
	unsigned int indexInEntityArray;
	Entity entity;
};

class ECS {
  private:
	/* Map containing components, each component type will be a key
	 * into this map, the value at each key will be the memory containing
	 * all of the components of this particular type (id) */
	std::unordered_map<unsigned int, ComponentMemory> m_Components;
	std::vector<EntityData *> m_Entities;

  public:
	ECS() = default;
	~ECS();

	/* Entity methods */
	EntityHandle MakeEntity(BaseECSComponent **entityComponents,
							const unsigned int *entityComponentIDs,
							size_t numComponents);
	void RemoveEntity(EntityHandle handle);

	/* TODO: Not sure if this actually works */
	template <class A, class... Args>
	EntityHandle MakeEntity(A &c, Args &... args) {
		static BaseECSComponent **components = nullptr;
		static unsigned int *componentIDs = nullptr;
		static int index = 0;
		if (components == nullptr) {
			size_t numComponents = (sizeof...(args) + sizeof(c)) / sizeof(c);
			components = new BaseECSComponent *[numComponents];
			componentIDs = new unsigned int[numComponents];
		} else {
			if constexpr (sizeof...(args) == 0) {
				EntityHandle handle = MakeEntity(
					components, componentIDs, static_cast<size_t>(index + 1));
				components = nullptr;
				componentIDs = nullptr;
				return handle;
			} else {
				components[index++] = &c;
				return MakeEntity(args...);
			}
		}
		return nullptr;
	}

	/* Component methods */
	template <class Component>
	void AddComponent(EntityHandle handle, Component *component) {
		AddComponentInternal(handle, HandleToEntity(handle), Component::ID,
							 component);
	}

	template <class Component>
	bool RemoveComponent(EntityHandle handle) {
		return RemoveComponentInternal(handle, Component::ID);
	}

	template <class Component>
	Component *GetComponent(EntityHandle handle) {
		return static_cast<Component *>(
			GetComponentInternal(HandleToEntity(handle),
								 m_Components[Component::ID], Component::ID));
	}

	/* System methods */
	void UpdateSystems(ECSSystemList &ecsSystemList, float deltaTime);

  private:
	EntityData *HandleToRawType(EntityHandle handle) {
		return static_cast<EntityData *>(handle);
	}

	Entity &HandleToEntity(EntityHandle handle) {
		return HandleToRawType(handle)->entity;
	}

	unsigned int HandleToEntityIndex(EntityHandle handle) {
		return HandleToRawType(handle)->indexInEntityArray;
	}

	void DeleteComponent(unsigned int componentID, unsigned int index);
	bool RemoveComponentInternal(EntityHandle handle, unsigned int componentID);

	void AddComponentInternal(EntityHandle handle, Entity &entity,
							  unsigned int componentID,
							  BaseECSComponent *component);

	BaseECSComponent *GetComponentInternal(Entity &entity,
										   ComponentMemory &memory,
										   unsigned int componentID);

	void UpdateSystemWithMultipleComponents(
		unsigned int index, ECSSystemList &ecsSystemList, float deltaTime,
		const std::vector<unsigned int> &componentTypes,
		std::vector<BaseECSComponent *> &componentParam,
		std::vector<ComponentMemory *> &componentArrays);

	unsigned int
	FindLeastCommonComponent(const std::vector<unsigned int> &componentTypes,
							 const std::vector<unsigned int> &componentFlags);

	/* No copying allowed */
	ECS(const ECS &other) = delete;
	void operator=(const ECS &other) = delete;
};

} // namespace renderel

#endif // ECS_HPP
