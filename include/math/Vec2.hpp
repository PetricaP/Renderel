#ifndef MATH_VEC2_HPP
#define MATH_VEC2_HPP

namespace renderel::math {

template <typename T> struct Vec2 {
	T x;
	T y;

	void add(const Vec2 &other);
	void sub(const Vec2 &other);
	void mul(const Vec2 &other);
	void div(const Vec2 &other);

	Vec2 &operator+=(const Vec2 &other);
	Vec2 &operator-=(const Vec2 &other);
	Vec2 &operator*=(const Vec2 &other);
	Vec2 &operator/=(const Vec2 &other);
};

template <typename T>
Vec2<T> operator+(const Vec2<T> &first, const Vec2<T> &second);

template <typename T>
Vec2<T> operator-(const Vec2<T> &first, const Vec2<T> &second);

template <typename T>
Vec2<T> operator*(const Vec2<T> &first, const Vec2<T> &second);

template <typename T>
Vec2<T> operator/(const Vec2<T> &first, const Vec2<T> &second);

} // namespace renderel::math

#endif // MATH_VEC2_HPP
