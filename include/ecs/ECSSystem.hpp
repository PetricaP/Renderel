#ifndef ECSSYSTEM_HPP
#define ECSSYSTEM_HPP

#include "ECSComponent.hpp"
#include <vector>

namespace renderel {

class BaseECSSystem {
  private:
	/* The component types on which the system operates */
	std::vector<uint32> m_ComponentTypes;
	std::vector<uint32> m_ComponentFlags;

  public:
	enum { FLAG_OPTIONAL = 1 };

	BaseECSSystem(const std::vector<uint32> &componentTypes)
		: m_ComponentTypes(componentTypes) {}
	virtual ~BaseECSSystem() = default;
	virtual void UpdateComponents(float, BaseECSComponent **) {}
	const std::vector<uint32> &GetComponentTypes() { return m_ComponentTypes; }

	const std::vector<uint32> &GetComponentFlags() { return m_ComponentFlags; }

	bool IsValid();

  protected:
	void AddComponentType(uint32 componentType, uint32 componentFlag = 0) {
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

	BaseECSSystem *operator[](uint32 index) { return m_Systems[index]; }
};

} // namespace renderel

#endif // ECSSYSTEM_HPP
