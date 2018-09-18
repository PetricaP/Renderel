#ifndef ECS_HPP
#define ECS_HPP

#include "ECSComponent.hpp"
#include "ECSSystem.hpp"
#include <unordered_map>

/* A component is generic so it's just an array of memory */
using ComponentMemory = std::vector<byte>;

/* We will use this ComponentData struct to easily refer
 * to any component an entity might have and manipulate it
 * the way we want */
struct ComponentData {
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

	EntityData *handleToRawType(EntityHandle handle) {
		return static_cast<EntityData *>(handle);
	}

	Entity &handleToEntity(EntityHandle handle) {
		return handleToRawType(handle)->entity;
	}

	unsigned int handleToEntityIndex(EntityHandle handle) {
		return handleToRawType(handle)->indexInEntityArray;
	}

  public:
	ECS() = default;
	~ECS();

	/* Entity methods */
	EntityHandle MakeEntity(BaseECSComponent *components,
							const unsigned int *componentIDs,
							size_t numComponents);
	void RemoveEntity(EntityHandle handle);

	/* Component methods */
	template <class Component>
	void AddComponent(EntityHandle handle);

	template <class Component>
	void RemoveComponent(EntityHandle handle);

	template <class Component>
	Component GetComponent(EntityHandle handle);

	/* System methods */
	void AddSystem(BaseECSSystem *system) { m_Systems.push_back(system); }
	void UpdateSystems(float deltaTime);
	void RemoveSystem(BaseECSSystem *system);

	/* No copying allowed */
	ECS(const ECS &other) = delete;
	void operator=(const ECS &other) = delete;
};

#endif // ECS_HPP
