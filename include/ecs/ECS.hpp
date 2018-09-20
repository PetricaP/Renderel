#ifndef ECS_HPP
#define ECS_HPP

#include "ECSComponent.hpp"
#include "ECSSystem.hpp"
#include "core/Common.hpp"
#include <unordered_map>

namespace renderel {

/* A component is generic so it's just an array of memory */
using ComponentMemory = std::vector<byte>;

/* We will use this ComponentData struct to easily refer
 * to any component an entity might have and manipulate it
 * the way we want */
struct ComponentData {
	/* The id of a component is it's type */
	uint32 componentType;
	uint32 keyInComponentMap;
};

/* All an entity is, is just a group of components */
using Entity = std::vector<ComponentData>;

struct EntityData {
	uint32 indexInEntityArray;
	Entity entity;
};

class ECS {
  private:
	/* Map containing components, each component type will be a key
	 * into this map, the value at each key will be the memory containing
	 * all of the components of this particular type (id) */
	std::unordered_map<uint32, ComponentMemory> m_Components;
	std::vector<EntityData *> m_Entities;

	/* Utilities for creating our parameters for the MakeEntity method */
	static BaseECSComponent **tempComponents;
	static uint32 *tempComponentIDs;
	static uint32 index;

  public:
	ECS() = default;
	~ECS();

	/* Entity methods */
	EntityHandle MakeEntity(BaseECSComponent **entityComponents,
							const uint32 *entityComponentIDs,
							size_t numComponents);
	void RemoveEntity(EntityHandle handle);

	/* TODO: Not sure if this actually works */
	template <class A, class... Args>
	EntityHandle MakeEntity(A &c, Args &... args) {
		/* TODO: I don't really want this check every time
		 *  MakeEntity is called */
		if (tempComponents == nullptr) {
			size_t numComponents = (sizeof...(args)) + 1;
			tempComponents = new BaseECSComponent *[numComponents];
			tempComponentIDs = new uint32[numComponents];
		}
		tempComponentIDs[index] = A::ID;
		tempComponents[index++] = &c;
		/* This is ok because it's compile time check */
		if constexpr (sizeof...(args) == 0) {
			EntityHandle handle = MakeEntity(tempComponents, tempComponentIDs,
											 static_cast<size_t>(index));
			tempComponents = nullptr;
			tempComponentIDs = nullptr;
			index = 0;
			return handle;
		} else {
			return MakeEntity(args...);
		}
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
		EntityData *entityData = static_cast<EntityData *>(handle);
		return entityData;
	}

	Entity &HandleToEntity(EntityHandle handle) {
		return HandleToRawType(handle)->entity;
	}

	uint32 HandleToEntityIndex(EntityHandle handle) {
		return HandleToRawType(handle)->indexInEntityArray;
	}

	void DeleteComponent(uint32 componentID, uint32 index);
	bool RemoveComponentInternal(EntityHandle handle, uint32 componentID);

	void AddComponentInternal(EntityHandle handle, Entity &entity,
							  uint32 componentID, BaseECSComponent *component);

	BaseECSComponent *GetComponentInternal(Entity &entity,
										   ComponentMemory &memory,
										   uint32 componentID);

	void UpdateSystemWithMultipleComponents(
		uint32 index, ECSSystemList &ecsSystemList, float deltaTime,
		const std::vector<uint32> &componentTypes,
		std::vector<BaseECSComponent *> &componentParam,
		std::vector<ComponentMemory *> &componentArrays);

	uint32 FindLeastCommonComponent(const std::vector<uint32> &componentTypes,
									const std::vector<uint32> &componentFlags);

	/* No copying allowed */
	ECS(const ECS &other) = delete;
	void operator=(const ECS &other) = delete;
};

} // namespace renderel

#endif // ECS_HPP
