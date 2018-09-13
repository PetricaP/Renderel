#ifndef MATH_QUATERNION_HPP
#define MATH_QUATERNION_HPP

#include "math/Vec3.hpp"
#include <iostream>

namespace renderel::math {

template <typename T = float>
struct Quaternion {
    union {
        struct {
            T x;
            T y;
            T z;
        };
        Vec3<T> v;
    };
    T w;

    Quaternion();
    Quaternion(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
    Quaternion(const Vec3<T> &axis, T angle);
    Quaternion Inverse() const;
    Quaternion operator^(T power) const;
    const Quaternion Slerp(const Quaternion &other, float t) const;
};

template <typename T>
Quaternion<T> Quaternion<T>::operator^(T power) const {
    return Quaternion(v, w * power);
}

template <typename T>
Quaternion<T> operator*(const Quaternion<T> &first,
                        const Quaternion<T> &second) {
    Quaternion<T> result;
    result.w = first.w * second.w - first.x * second.x - first.y * second.y -
               first.z * second.z;
    result.x = first.w * second.x + first.x * second.w + first.y * second.z -
               first.z * second.y;
    result.y = first.w * second.y - first.x * second.z + first.y * second.w +
               first.z * second.x;
    result.z = first.w * second.z + first.x * second.y - first.y * second.x +
               first.z * second.w;
    return result;
}

template <typename T>
const Quaternion<T> Quaternion<T>::Slerp(const Quaternion &other,
                                         float t) const {
    return ((other * Inverse()) ^ t) * *this;
}

template <typename T>
Vec3<T> operator*(const Quaternion<T> &q, const Vec3<T> &v) {
    Quaternion<T> vq(v.x, v.y, v.z, 0);
    Quaternion<T> res = q * vq * q.Inverse();
    return res.v;
}

template <typename T>
Quaternion<T>::Quaternion() {
    memset(this, 0, sizeof(Quaternion<T>));
}

template <typename T>
Quaternion<T>::Quaternion(const Vec3<T> &axis, T angle) {
    T halfAngleInRadians = toRadians(angle) / 2;
    T s = sin(halfAngleInRadians);
    T c = cos(halfAngleInRadians);
    v = s * axis;
    w = c;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Quaternion<T> &q) {
    std::cout << q.w << " + " << q.x << " * i + " << q.y << " * j + " << q.z
              << " * k";
    return os;
}

template <typename T>
Quaternion<T> Quaternion<T>::Inverse() const {
    Quaternion<T> inverse;
    inverse.v = -v;
    inverse.w = w;
    return inverse;
}

} // namespace renderel::math

#endif // QUATERNION_HPP
