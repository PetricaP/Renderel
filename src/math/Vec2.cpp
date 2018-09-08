#include "math/Vec2.hpp"

namespace renderel::math {
template<typename T>
void Vec2<T>::add(const Vec2<T> &other) {
	x += other.x;
	y += other.y;
}

template<typename T>
void Vec2<T>::sub(const Vec2<T> &other) {
	x -= other.x;
	y -= other.y;
}

template<typename T>
void Vec2<T>::mul(const Vec2<T> &other) {
	x *= other.x;
	y *= other.y;
}

template<typename T>
void Vec2<T>::div(const Vec2<T> &other) {
	x /= other.x;
	y /= other.y;
}

template<typename T>
Vec2<T> &Vec2<T>::operator+=(const Vec2<T> &other) {
	add(other);
}

template<typename T>
Vec2<T> &Vec2<T>::operator-=(const Vec2<T> &other) {
	sub(other);
}

template<typename T>
Vec2<T> &Vec2<T>::operator*=(const Vec2<T> &other) {
	mul(other);
}

template<typename T>
Vec2<T> &Vec2<T>::operator/=(const Vec2<T> &other) {
	div(other);
}

template<typename T>
Vec2<T> operator+(const Vec2<T> &first, const Vec2<T> &second) {
	return { first.x + second.x, first.y + second.y };
}

template<typename T>
Vec2<T> operator-(const Vec2<T> &first, const Vec2<T> &second) {
	return { first.x - second.x, first.y - second.y };
}

template<typename T>
Vec2<T> operator*(const Vec2<T> &first, const Vec2<T> &second) {
	return { first.x * second.x, first.y * second.y };
}

template<typename T>
Vec2<T> operator/(const Vec2<T> &first, const Vec2<T> &second) {
	return { first.x / second.x, first.y / second.y };
}
