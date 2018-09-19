#ifndef ECSSYSTEM_HPP
#define ECSSYSTEM_HPP

#include "ECSComponent.hpp"
#include <vector>

namespace renderel {

class BaseECSSystem {
  private:
	std::vector<unsigned int> m_ComponentTypes;

  public:
	BaseECSSystem(const std::vector<unsigned int> &componentTypes)
		: m_ComponentTypes(componentTypes) {}
	virtual ~BaseECSSystem() = default;
	virtual void UpdateComponents(float deltaTime,
								  BaseECSComponent **components) {}
	const std::vector<unsigned int> &GetComponentTypes() {
		return m_ComponentTypes;
	}
};

} // namespace renderel

#endif // ECSSYSTEM_HPP