#ifndef EULERANGLE_HPP
#define EULERANGLE_HPP

#include "math/Vec3.hpp"

namespace renderel::math {

template <typename T = float>
struct EulerAngle {
	T pitch = 0;
	T yaw = 0;
	T roll = 0;

	EulerAngle(T pitch, T yaw, T roll) : pitch(pitch), yaw(yaw), roll(roll) {}

	Vec3<T> ToVector() const;
	void Normalize();
	void Add(T pitch, T yaw, T roll);
};

template <typename T>
Vec3<T> EulerAngle<T>::ToVector() const {
	Vec3<T> result;

	result.x = cos(toRadians(yaw)) * cos(toRadians(pitch));
	result.y = sin(toRadians(pitch));
	result.z = sin(toRadians(yaw)) * cos(toRadians(pitch));

	return result;
}

template <typename T>
void EulerAngle<T>::Add(T pitch, T yaw, T roll) {
	this->pitch += pitch;
	this->yaw += yaw;
	this->roll += roll;
}

template <typename T>
void EulerAngle<T>::Normalize() {
	if (pitch > 89) {
		pitch = 89;
	} else if (pitch < -89) {
		pitch = -89;
	}

	while (yaw > 180) {
		yaw -= 360;
	}
	while (yaw < -180) {
		yaw += 360;
	}
}

} // namespace renderel::math

#endif // EULERANGLE_HPP
