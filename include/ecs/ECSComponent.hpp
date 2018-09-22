#ifndef ECSCOMPONENT_HPP
#define ECSCOMPONENT_HPP

#include "core/Common.hpp"
#include <cstdlib>
#include <memory>
#include <vector>

namespace renderel {

/* The component shouldn't really know anything
 * about the entity it's attached to, but should
 * have a way to reference it. */
using EntityHandle = void *;
#define NULL_ENTITY_HANDLE nullptr

/* Renaming so it makes more sense, because it's jut a
 * block of memory */
using byte = uint8;

struct BaseECSComponent;

/* Typedefs for our functions so it won't be a pain to type */
typedef uint32 (*ECSComponentCreateFunction)(std::vector<byte> &memory,
											 EntityHandle entity,
											 BaseECSComponent *components);

typedef void (*ECSComponentFreeFunction)(BaseECSComponent *freeComponent);

struct BaseECSComponentData {
	ECSComponentCreateFunction createFunction;
	ECSComponentFreeFunction freeFunction;
	size_t size;
	BaseECSComponentData(ECSComponentCreateFunction createFunction,
						 ECSComponentFreeFunction freeFunction, size_t size)
		: createFunction(createFunction), freeFunction(freeFunction),
		  size(size) {}
};

/* Every component will contain an ID and a handle
 * for the entity it is attached to */
struct BaseECSComponent {
  private:
	static std::vector<BaseECSComponentData> *m_ComponentTypes;

  public:
	static uint32
	RegisterComponentType(ECSComponentCreateFunction createFunction,
						  ECSComponentFreeFunction freeFunction, size_t size);
	EntityHandle entityHandle = NULL_ENTITY_HANDLE;

	static ECSComponentCreateFunction GetTypeCreateFunction(uint32 id) {
		return (*m_ComponentTypes)[id].createFunction;
	}

	static ECSComponentFreeFunction GetTypeFreeFunction(uint32 id) {
		return (*m_ComponentTypes)[id].freeFunction;
	}

	static size_t GetTypeSize(uint32 id) {
		return (*m_ComponentTypes)[id].size;
	}

	static bool IsTypeValid(uint32 id) { return id < m_ComponentTypes->size(); }
};

/* These will be the "constructors" and "destructors" for our components */
template <typename Component>
uint32 ECSComponentCreate(std::vector<byte> &memory, EntityHandle handle,
						  BaseECSComponent *component) {
	uint32 index = static_cast<uint32>(memory.size());
	memory.resize(index + Component::SIZE);

	std::unique_ptr<Component> comp(
		new (&memory[index]) Component(*static_cast<Component *>(component)));

	comp.release();
	component->entityHandle = handle;
	return index;
}

template <typename Component>
void ECSComponentFree(BaseECSComponent *freeComponent) {
	Component *component = static_cast<Component *>(freeComponent);
	component->~Component();
}

/* Here we're using the curiously recurring template pattern to
 * free us from the burdon of manually defining the these 4 members
 * for our components */
template <typename T>
struct ECSComponent : public BaseECSComponent {
  public:
	static const ECSComponentCreateFunction CREATEFUNCTION;
	static const ECSComponentFreeFunction FREEFUNCTION;
	static const uint32 ID;
	static const size_t SIZE;
};

/* Initialize all the static members */

template <typename T>
const uint32 ECSComponent<T>::ID(BaseECSComponent::RegisterComponentType(
	ECSComponentCreate<T>, ECSComponentFree<T>, sizeof(T)));

template <typename T>
const size_t ECSComponent<T>::SIZE(sizeof(T));

template <typename T>
const ECSComponentCreateFunction
	ECSComponent<T>::CREATEFUNCTION(ECSComponentCreate<T>);

template <typename T>
const ECSComponentFreeFunction
	ECSComponent<T>::FREEFUNCTION(ECSComponentFree<T>);

/* This is how a game component should be declared */
struct TestComponent : public ECSComponent<TestComponent> {
	float x;
	float y;
};

} // namespace renderel

#endif // ECSCOMPONENT_HPP
