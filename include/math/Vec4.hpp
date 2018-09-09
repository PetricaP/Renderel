#ifndef MATH_VEC4_HPP
#define MATH_VEC4_HPP

#include <iostream>

namespace renderel::math {

template <typename T>
union Vec4 {
    T x;
    T y;
    T z;
    T w;

    Vec4();
    Vec4(T x, T y, T z, T w);

	void add(const Vec4 &other);
    void sub(const Vec4 &other);
    void mul(const Vec4 &other);
    void div(const Vec4 &other);

	Vec4 &operator+=(const Vec4 &other);
	Vec4 &operator-=(const Vec4 &other);
	Vec4 &operator*=(const Vec4 &other);
	Vec4 &operator/=(const Vec4 &other);

	T &operator[](unsigned int index);
	T operator[](unsigned int index) const;
};

template <typename T>
T &Vec4<T>::operator[](unsigned int index) {
	switch(index) {
		case 1:
			return y;
		case 2:
			return z;
		case 3:
			return w;
		default:
			return x;
	}
}

template <typename T>
T Vec4<T>::operator[](unsigned int index) const {
	switch(index) {
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		case 3:
			return w;
	}
	return 0;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vec4<T>& vec) {
    std::cout << "Vec4(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
    return os;
}

template <typename T>
Vec4<T>::Vec4() :
    x(0), y(0), z(0), w(0) { }

template <typename T>
Vec4<T>::Vec4(T x, T y, T z, T w) :
    x(x), y(y), z(z), w(w) { } 

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
Vec4<T> operator+(const Vec4<T> &first, const Vec4<T> &second) {
	return {first.x + second.x, first.y + second.y, first.z + second.z, first.w + second.z};
}

template <typename T>
Vec4<T> operator-(const Vec4<T> &first, const Vec4<T> &second) {
	return {first.x - second.x, first.y - second.y, first.z - second.z, first.w - second.z};
}

template <typename T>
Vec4<T> operator*(const Vec4<T> &first, const Vec4<T> &second) {
	return {first.x * second.x, first.y * second.y, first.z * second.z, first.w * second.z};
}

template <typename T>
Vec4<T> operator/(const Vec4<T> &first, const Vec4<T> &second) {
	return {first.x / second.x, first.y / second.y, first.z / second.z, first.w / second.z};
}

} //namespace renderel::math

#endif // MATH_VEC4_HPP
