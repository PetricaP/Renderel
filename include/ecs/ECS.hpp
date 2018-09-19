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
	std::vector<BaseECSSystem *> m_Systems;
	std::unordered_map<unsigned int, ComponentMemory> m_Components;
	std::vector<EntityData *> m_Entities;

  public:
	ECS() = default;
	~ECS();

	/* Entity methods */
	EntityHandle MakeEntity(BaseECSComponent components[],
							const unsigned int componentIDs[],
							size_t numComponents);
	void RemoveEntity(EntityHandle handle);

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
		return GetComponentInternal(HandleToEntity(handle),
									m_Components[Component::ID], Component::ID);
	}

	/* System methods */
	void AddSystem(BaseECSSystem *system) { m_Systems.push_back(system); }
	bool RemoveSystem(BaseECSSystem &system);
	void UpdateSystems(float deltaTime);

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
										   std::vector<byte> &memory,
										   unsigned int componentID);

	void UpdateSystemWithMultipleComponents(
		unsigned int index, float deltaTime,
		const std::vector<unsigned int> &componentTypes,
		std::vector<BaseECSComponent *> &componentParam,
		std::vector<std::vector<byte> *> &componentArrays);

	/* No copying allowed */
	ECS(const ECS &other) = delete;
	void operator=(const ECS &other) = delete;
};

} // namespace renderel

#endif // ECS_HPP
