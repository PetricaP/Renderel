#ifndef MATH_VEC3_HPP
#define MATH_VEC3_HPP

#include "core/Common.hpp"
#include <cmath>
#include <iostream>

namespace renderel::math {

template <typename T = float>
union Vec3 {
	// Position
	struct {
		T x, y, z;
	};
	// Color
	struct {
		T r, g, b;
	};
	// Texture
	struct {
		T u, v, w;
	};
	T elements[3];

	Vec3();
	Vec3(T t);
	Vec3(T x, T y, T z);

	void add(const Vec3 &other);
	void sub(const Vec3 &other);
	void mul(const Vec3 &other);
	void div(const Vec3 &other);

	Vec3 &operator+=(const Vec3 &other);
	Vec3 &operator-=(const Vec3 &other);
	Vec3 &operator*=(const Vec3 &other);
	Vec3 &operator/=(const Vec3 &other);

	bool operator==(const Vec3 &other) const;

	Vec3 operator-() const;

	Vec3 &operator+=(T t);
	Vec3 &operator-=(T t);
	Vec3 &operator*=(T t);
	Vec3 &operator/=(T t);

	Vec3 Cross(const Vec3 &other);
	T Dot(const Vec3 &other);

	T Length() const;
	Vec3 Normalize() const;

	T &operator[](uint32 index);
	T operator[](uint32 index) const;
};

template <typename T>
Vec3<T> Vec3<T>::Normalize() const {
	return *this / Length();
}

template <typename T>
T Vec3<T>::Length() const {
	return sqrt(x * x + y * y + z * z);
}

template <typename T>
Vec3<T> Vec3<T>::operator-() const {
	return Vec3<T>(-x, -y, -z);
}

template <typename T>
T &Vec3<T>::operator[](uint32 index) {
	return elements[index];
}

template <typename T>
T Vec3<T>::operator[](uint32 index) const {
	return elements[index];
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Vec3<T> &vec) {
	std::cout << "Vec3(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
	return os;
}

template <typename T>
Vec3<T>::Vec3() : x(0), y(0), z(0) {}

template <typename T>
Vec3<T>::Vec3(T t) : x(t), y(t), z(t) {}

template <typename T>
Vec3<T>::Vec3(T x, T y, T z) : x(x), y(y), z(z) {}

template <typename T>
void Vec3<T>::add(const Vec3 &other) {
	x += other.x;
	y += other.y;
	z += other.z;
}

template <typename T>
void Vec3<T>::sub(const Vec3 &other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
}

template <typename T>
void Vec3<T>::mul(const Vec3 &other) {
	x *= other.x;
	y *= other.y;
	z *= other.z;
}

template <typename T>
void Vec3<T>::div(const Vec3 &other) {
	x /= other.x;
	y /= other.y;
	z /= other.z;
}

template <typename T>
Vec3<T> Vec3<T>::Cross(const Vec3<T> &other) {
	return Vec3<T>(y * other.z - z * other.y, z * other.x - x * other.z,
				   x * other.y - y * other.x);
}

template <typename T>
T Vec3<T>::Dot(const Vec3<T> &other) {
	return x * other.x + y * other.y + z * other.z;
}

template <typename T>
bool Vec3<T>::operator==(const Vec3<T> &other) const {
	return x == other.x && y == other.y && z == other.z;
}

template <typename T>
Vec3<T> &Vec3<T>::operator+=(const Vec3<T> &other) {
	add(other);
	return *this;
}

template <typename T>
Vec3<T> &Vec3<T>::operator-=(const Vec3<T> &other) {
	sub(other);
	return *this;
}

template <typename T>
Vec3<T> &Vec3<T>::operator*=(const Vec3<T> &other) {
	mul(other);
	return *this;
}

template <typename T>
Vec3<T> &Vec3<T>::operator/=(const Vec3<T> &other) {
	div(other);
	return *this;
}

template <typename T>
Vec3<T> &Vec3<T>::operator+=(T t) {
	x += t;
	y += t;
	z += t;
	return *this;
}

template <typename T>
Vec3<T> &Vec3<T>::operator-=(T t) {
	x -= t;
	y -= t;
	z -= t;
	return *this;
}

template <typename T>
Vec3<T> &Vec3<T>::operator*=(T t) {
	x *= t;
	y *= t;
	z *= t;
	return *this;
}

template <typename T>
Vec3<T> &Vec3<T>::operator/=(T t) {
	x /= t;
	y /= t;
	z /= t;
	return *this;
}

template <typename T>
Vec3<T> operator+(const Vec3<T> &first, const Vec3<T> &second) {
	return {first.x + second.x, first.y + second.y, first.z + second.z};
}

template <typename T>
Vec3<T> operator-(const Vec3<T> &first, const Vec3<T> &second) {
	return {first.x - second.x, first.y - second.y, first.z - second.z};
}

template <typename T>
Vec3<T> operator*(const Vec3<T> &first, const Vec3<T> &second) {
	return {first.x * second.x, first.y * second.y, first.z * second.z};
}

template <typename T>
Vec3<T> operator*(const Vec3<T> &vec, T scalar) {
	return {vec.x * scalar, vec.y * scalar, vec.z * scalar};
}

template <typename T>
Vec3<T> operator/(const Vec3<T> &first, const Vec3<T> &second) {
	return {first.x / second.x, first.y / second.y, first.z / second.z};
}

template <typename T>
Vec3<T> operator+(const Vec3<T> &vec, T t) {
	return {vec.x + t, vec.y + t, vec.z + t};
}

template <typename T>
Vec3<T> operator-(const Vec3<T> &vec, T t) {
	return {vec.x - t, vec.y - t, vec.z - t};
}

template <typename T>
Vec3<T> operator/(const Vec3<T> &vec, T t) {
	return {vec.x / t, vec.y / t, vec.z / t};
}

template <typename T>
Vec3<T> operator+(T t, const Vec3<T> &vec) {
	return {vec.x + t, vec.y + t, vec.z + t};
}

template <typename T>
Vec3<T> operator-(T t, const Vec3<T> &vec) {
	return {t - vec.x, t - vec.y, t - vec.z};
}

template <typename T>
Vec3<T> operator*(T t, const Vec3<T> &vec) {
	return {vec.x * t, vec.y * t, vec.z * t};
}

template <typename T>
Vec3<T> operator/(T t, const Vec3<T> &vec) {
	return {vec.x / t, vec.y / t, vec.z / t};
}

typedef Vec3<float> dVec3;

} // namespace renderel::math

#endif // MATH_VEC3_HPP
