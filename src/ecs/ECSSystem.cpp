#include "ecs/ECSSystem.hpp"

namespace renderel {

bool BaseECSSystem::IsValid() {
	for (unsigned int i = 0; i < m_ComponentFlags.size(); ++i) {
		if ((m_ComponentFlags[i] & BaseECSSystem::FLAG_OPTIONAL) == 0) {
			return true;
		}
	}
	return false;
}

bool ECSSystemList::RemoveSystem(BaseECSSystem &system) {
	for (unsigned int i = 0; i < m_Systems.size(); ++i) {
		if (&system == m_Systems[i]) {
			m_Systems.erase(m_Systems.begin() + i);
			return true;
		}
	}
	return false;
}

} // namespace renderel
