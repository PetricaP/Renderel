#include "ecs/ECSComponent.hpp"

std::vector<BaseECSComponentData> BaseECSComponent::m_ComponentTypes;

unsigned int BaseECSComponent::RegisterComponentType(
	ECSComponentCreateFunction createFunction,
	ECSComponentFreeFunction freeFunction, size_t size) {

	unsigned int componentID =
		static_cast<unsigned int>(m_ComponentTypes.size());

	m_ComponentTypes.push_back(
		BaseECSComponentData(createFunction, freeFunction, size));

	return componentID;
}
