#ifndef ECSCOMPONENT_HPP
#define ECSCOMPONENT_HPP

#include <cstdlib>
#include <vector>

namespace renderel {

/* The component shouldn't really know anything
 * about the entity it's attached to, but should
 * have a way to reference it. */
using EntityHandle = void *;
#define NULL_ENTITY_HANDLE nullptr

/* Renaming so it makes more sense, because it's jut a
 * block of memory */
using byte = unsigned char;

struct BaseECSComponent;

/* Typedefs for our functions so it won't be a pain to type */
typedef unsigned int (*ECSComponentCreateFunction)(
	std::vector<byte> &memory, EntityHandle entity,
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
	static unsigned int
	RegisterComponentType(ECSComponentCreateFunction createFunction,
						  ECSComponentFreeFunction freeFunction, size_t size);
	EntityHandle entityHandle = NULL_ENTITY_HANDLE;

	static ECSComponentCreateFunction GetTypeCreateFunction(unsigned int id) {
		return (*m_ComponentTypes)[id].createFunction;
	}

	static ECSComponentFreeFunction GetTypeFreeFunction(unsigned int id) {
		return (*m_ComponentTypes)[id].freeFunction;
	}

	static size_t GetTypeSize(unsigned int id) {
		return (*m_ComponentTypes)[id].size;
	}

	static bool IsTypeValid(unsigned int id) {
		return id < m_ComponentTypes->size();
	}
};

/* These will be the "constructors" and "destructors" for our components */
template <typename Component>
unsigned int ECSComponentCreate(std::vector<byte> &memory, EntityHandle handle,
								BaseECSComponent *components) {
	unsigned int index = static_cast<unsigned int>(memory.size());
	memory.resize(index + Component::SIZE);
	Component *component =
		new (&memory[index]) Component(*static_cast<Component *>(components));
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
	static const unsigned int ID;
	static const size_t SIZE;
};

/* Initialize all the static members */

template <typename T>
const unsigned int ECSComponent<T>::ID(BaseECSComponent::RegisterComponentType(
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
