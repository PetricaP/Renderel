#ifndef MATH_VEC4_HPP
#define MATH_VEC4_HPP

#include "math/Vec3.hpp"
#include <iostream>

namespace renderel::math {

template <typename T = float>
union Vec4 {
	// Position
	struct {
		T x, y, z, w;
	};
	// Color
	struct {
		T r, g, b, a;
	};
	T elements[4];

	Vec4();
	Vec4(T t);
	Vec4(T x, T y, T z, T w);
	Vec4(Vec3<T> v, T w);

	void add(const Vec4 &other);
	void sub(const Vec4 &other);
	void mul(const Vec4 &other);
	void div(const Vec4 &other);

	Vec4 &operator+=(const Vec4 &other);
	Vec4 &operator-=(const Vec4 &other);
	Vec4 &operator*=(const Vec4 &other);
	Vec4 &operator/=(const Vec4 &other);

	bool operator==(const Vec4 &other) const;

	Vec4 &operator+=(T t);
	Vec4 &operator-=(T t);
	Vec4 &operator*=(T t);
	Vec4 &operator/=(T t);

	T &operator[](unsigned int index);
	T operator[](unsigned int index) const;
};

template <typename T>
T &Vec4<T>::operator[](unsigned int index) {
	return elements[index];
}

template <typename T>
T Vec4<T>::operator[](unsigned int index) const {
	return elements[index];
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Vec4<T> &vec) {
	std::cout << "Vec4(" << vec.x << ", " << vec.y << ", " << vec.z << ", "
			  << vec.w << ")";
	return os;
}

template <typename T>
Vec4<T>::Vec4() : x(0), y(0), z(0), w(0) {}

template <typename T>
Vec4<T>::Vec4(T t) : x(t), y(t), z(t), w(t) {}

template <typename T>
Vec4<T>::Vec4(Vec3<T> v, T w) : x(v.x), y(v.y), z(v.z), w(w) {}

template <typename T>
Vec4<T>::Vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

template <typename T>
void Vec4<T>::add(const Vec4 &other) {
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;
}

template <typename T>
void Vec4<T>::sub(const Vec4 &other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;
}

template <typename T>
void Vec4<T>::mul(const Vec4 &other) {
	x *= other.x;
	y *= other.y;
	z *= other.z;
	w *= other.w;
}

template <typename T>
void Vec4<T>::div(const Vec4 &other) {
	x /= other.x;
	y /= other.y;
	z /= other.z;
	w /= other.w;
}

template <typename T>
bool Vec4<T>::operator==(const Vec4<T> &other) const {
	return x == other.x && y == other.y && z == other.z && w == other.w;
}

template <typename T>
Vec4<T> &Vec4<T>::operator+=(const Vec4<T> &other) {
	add(other);
	return *this;
}

template <typename T>
Vec4<T> &Vec4<T>::operator-=(const Vec4<T> &other) {
	sub(other);
	return *this;
}

template <typename T>
Vec4<T> &Vec4<T>::operator*=(const Vec4<T> &other) {
	mul(other);
	return *this;
}

template <typename T>
Vec4<T> &Vec4<T>::operator/=(const Vec4<T> &other) {
	div(other);
	return *this;
}

template <typename T>
Vec4<T> &Vec4<T>::operator+=(T t) {
	x += t;
	y += t;
	z += t;
	w += t;
	return *this;
}

template <typename T>
Vec4<T> &Vec4<T>::operator-=(T t) {
	x -= t;
	y -= t;
	z -= t;
	w -= t;
	return *this;
}

template <typename T>
Vec4<T> &Vec4<T>::operator*=(T t) {
	x *= t;
	y *= t;
	z *= t;
	w *= t;
	return *this;
}

template <typename T>
Vec4<T> &Vec4<T>::operator/=(T t) {
	x /= t;
	y /= t;
	z /= t;
	w /= t;
	return *this;
}

template <typename T>
Vec4<T> operator+(const Vec4<T> &first, const Vec4<T> &second) {
	return {first.x + second.x, first.y + second.y, first.z + second.z,
			first.w + second.z};
}

template <typename T>
Vec4<T> operator-(const Vec4<T> &first, const Vec4<T> &second) {
	return {first.x - second.x, first.y - second.y, first.z - second.z,
			first.w - second.z};
}

template <typename T>
Vec4<T> operator*(const Vec4<T> &first, const Vec4<T> &second) {
	return {first.x * second.x, first.y * second.y, first.z * second.z,
			first.w * second.z};
}

template <typename T>
Vec4<T> operator/(const Vec4<T> &first, const Vec4<T> &second) {
	return {first.x / second.x, first.y / second.y, first.z / second.z,
			first.w / second.z};
}

template <typename T>
Vec4<T> operator+(const Vec4<T> &vec, T t) {
	return {vec.x + t, vec.y + t, vec.z + t, vec.w + t};
}

template <typename T>
Vec4<T> operator-(const Vec4<T> &vec, T t) {
	return {vec.x - t, vec.y - t, vec.z - t, vec.w - t};
}

template <typename T>
Vec4<T> operator*(const Vec4<T> &vec, T t) {
	return {vec.x * t, vec.y * t, vec.z * t, vec.w * t};
}

template <typename T>
Vec4<T> operator/(const Vec4<T> &vec, T t) {
	return {vec.x / t, vec.y / t, vec.z / t, vec.w / t};
}

template <typename T>
Vec4<T> operator+(T t, const Vec4<T> &vec) {
	return {vec.x + t, vec.y + t, vec.z + t, vec.w + t};
}

template <typename T>
Vec4<T> operator-(T t, const Vec4<T> &vec) {
	return {t - vec.x, t - vec.y, t - vec.z, t - vec.w};
}

template <typename T>
Vec4<T> operator*(T t, const Vec4<T> &vec) {
	return {vec.x * t, vec.y * t, vec.z * t, vec.w * t};
}

template <typename T>
Vec4<T> operator/(T t, const Vec4<T> &vec) {
	return {vec.x / t, vec.y / t, vec.z / t, vec.w / t};
}

} // namespace renderel::math

#endif // MATH_VEC4_HPP
