#ifndef MATH_VEC3_HPP
#define MATH_VEC3_HPP

#include <iostream>

namespace renderel::math {

template <typename T>
union Vec3 {
    struct {
		T x, y, z;
    };
	T elements[3];

	Vec3();
	Vec3(T x, T y, T z);

	void add(const Vec3 &other);
	void sub(const Vec3 &other);
	void mul(const Vec3 &other);
	void div(const Vec3 &other);

	Vec3 &operator+=(const Vec3 &other);
	Vec3 &operator-=(const Vec3 &other);
	Vec3 &operator*=(const Vec3 &other);
	Vec3 &operator/=(const Vec3 &other);

	T &operator[](unsigned int index);
	T operator[](unsigned int index) const;
};

template <typename T>
T &Vec3<T>::operator[](unsigned int index) {
	return elements[index];
}

template <typename T>
T Vec3<T>::operator[](unsigned int index) const {
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
Vec3<T> operator/(const Vec3<T> &first, const Vec3<T> &second) {
	return {first.x / second.x, first.y / second.y, first.z / second.z};
}

} // namespace renderel::math

#endif // MATH_VEC3_HPP
