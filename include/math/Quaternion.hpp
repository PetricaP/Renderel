#ifndef MATH_QUATERNION_HPP
#define MATH_QUATERNION_HPP

#include "math/Mat4.hpp"
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
    Mat4<T> ToRotationMatrix() const;
    // TODO: implement Slerp
    const Quaternion Slerp(const Quaternion &other, float t) const;
};

template <typename T>
Quaternion<T> Quaternion<T>::operator^(T power) const {
    return Quaternion(v, w * power);
}

template <typename T>
Mat4<T> Quaternion<T>::ToRotationMatrix() const {
    Mat4<T> mat;
    mat[0][0] = 1 - 2 * y * y - 2 * z * z;
    mat[0][1] = 2 * x * y - 2 * z * w;
    mat[0][2] = 2 * x * z + 2 * y * w;
    mat[0][3] = 0;

    mat[1][0] = 2 * x * y + 2 * z * w;
    mat[1][1] = 1 - 2 * x * x - 2 * z * z;
    mat[1][2] = 2 * y * z - 2 * x * 2;
    mat[1][3] = 0;

    mat[2][0] = 2 * x * z - 2 * y * w;
    mat[2][1] = 2 * y * z + 2 * x * w;
    mat[2][2] = 1 - 2 * x * x - 2 * y * y;
    mat[2][3] = 0;

    mat[3][0] = 0;
    mat[3][1] = 0;
    mat[3][2] = 0;
    mat[3][3] = 1;
    return mat;
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
