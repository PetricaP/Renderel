#include "ecs/ECSComponent.hpp"

namespace renderel {

/* Defaults to nullptr */
std::vector<BaseECSComponentData> *BaseECSComponent::m_ComponentTypes;

uint32 BaseECSComponent::RegisterComponentType(
	ECSComponentCreateFunction createFunction,
	ECSComponentFreeFunction freeFunction, size_t size) {

	if (m_ComponentTypes == nullptr) {
		m_ComponentTypes = new std::vector<BaseECSComponentData>;
	}

	uint32 componentID = static_cast<uint32>(m_ComponentTypes->size());

	m_ComponentTypes->push_back(
		BaseECSComponentData(createFunction, freeFunction, size));

	return componentID;
}

} // namespace renderel
