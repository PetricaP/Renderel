#ifndef ECSSYSTEM_HPP
#define ECSSYSTEM_HPP

#include "ECSComponent.hpp"
#include <vector>

namespace renderel {

class BaseECSSystem {
  private:
	/* The component types on which the system operates */
	std::vector<unsigned int> m_ComponentTypes;
	std::vector<unsigned int> m_ComponentFlags;

  public:
	enum { FLAG_OPTIONAL = 1 };

	BaseECSSystem(const std::vector<unsigned int> &componentTypes)
		: m_ComponentTypes(componentTypes) {}
	virtual ~BaseECSSystem() = default;
	virtual void UpdateComponents(float deltaTime,
								  BaseECSComponent **components) {}
	const std::vector<unsigned int> &GetComponentTypes() {
		return m_ComponentTypes;
	}

	const std::vector<unsigned int> &GetComponentFlags() {
		return m_ComponentFlags;
	}

	bool IsValid();

  protected:
	void AddComponentType(unsigned int componentType,
						  unsigned int componentFlag = 0) {
		m_ComponentTypes.push_back(componentType);
		m_ComponentFlags.push_back(componentFlag);
	}
};

class ECSSystemList {
  private:
	std::vector<BaseECSSystem *> m_Systems;

  public:
	bool AddSystem(BaseECSSystem *system) {
		if (!system->IsValid()) {
			return false;
		}
		m_Systems.push_back(system);
		return true;
	}
	bool RemoveSystem(BaseECSSystem &system);
	size_t size() { return m_Systems.size(); }

	BaseECSSystem *operator[](unsigned int index) { return m_Systems[index]; }
};

} // namespace renderel

#endif // ECSSYSTEM_HPP
