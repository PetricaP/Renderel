#ifndef EULERANGLE_HPP
#define EULERANGLE_HPP

#include "math/Vec3.hpp"

namespace renderel::math {

template <typename T = float>
class EulerAngle {
  private:
	T m_Pitch = 0;
	T m_Yaw = 0;
	T m_Roll = 0;

  public:
	EulerAngle(T pitch, T yaw, T roll)
		: m_Pitch(pitch), m_Yaw(yaw), m_Roll(roll) {}

	Vec3<T> ToVector() const;
	void Normalize();
	void Add(T pitch, T yaw, T roll);

	void SetPitch(T pitch) { m_Pitch = pitch; }
	void SetYaw(T yaw) { m_Yaw = yaw; }
	void SetRoll(T roll) { m_Roll = roll; }

	T GetPitch() { return m_Pitch; }
	T GetYaw() { return m_Yaw; }
	T GetRoll() { return m_Roll; }
};

template <typename T>
Vec3<T> EulerAngle<T>::ToVector() const {
	Vec3<T> result;

	result.x = cos(m_Yaw) * cos(m_Pitch);
	result.y = sin(m_Pitch);
	result.z = sin(m_Yaw) * cos(m_Pitch);

	return result;
}

template <typename T>
void EulerAngle<T>::Add(T pitch, T yaw, T roll) {
	m_Pitch += pitch;
	m_Yaw += yaw;
	m_Roll += roll;
}

template <typename T>
void EulerAngle<T>::Normalize() {
	if (m_Pitch > 89) {
		m_Pitch = 89;
	} else if (m_Pitch < -89) {
		m_Pitch = -89;
	}

	if (m_Yaw > 180) {
		m_Yaw -= 360;
	} else if (m_Yaw < -180) {
		m_Yaw += 360;
	}
}

} // namespace renderel::math

#endif // EULERANGLE_HPP
