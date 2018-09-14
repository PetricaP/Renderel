#ifndef MATH_MAT4_HPP
#define MATH_MAT4_HPP

#include "math/Vec3.hpp"
#include "math/Vec4.hpp"
#include <cmath>
#include <cstring>
#include <iostream>

namespace renderel::math {

template <typename T = float>
union Mat4 {
	T elements[4][4];
	Vec4<T> vecs[4];

	Mat4();
	Mat4(T diag);

	Vec4<T> operator[](unsigned int index) const;
	Vec4<T> &operator[](unsigned int index);

    static Mat4 Ortho(T left, T right, T bottom, T top, T near, T far);
    static Mat4 Perspective(T fov, T aspectRatio, T near, T far);
    static Mat4 Translation(const Vec3<T> &amount);
	static Mat4 Scale(const Vec3<T> &scale);
    static Mat4 LookAt(const Vec3<T> &eye, const Vec3<T> &at,
                       const Vec3<T> &up);
};

template <typename T>
Vec4<T> Mat4<T>::operator[](unsigned int index) const {
	return vecs[index];
}

template <typename T>
Vec4<T> &Mat4<T>::operator[](unsigned int index) {
	return vecs[index];
}

template <typename T>
Mat4<T> Mat4<T>::LookAt(const Vec3<T> &eye, const Vec3<T> &at,
                        const Vec3<T> &up) {
    Vec3<> zAxis = (eye - at).Normalize();
    Vec3<> xAxis = zAxis.Cross(up).Normalize();
    Vec3<> yAxis = up.Normalize();
}

template <typename T>
Mat4<T> Mat4<T>::Scale(const Vec3<T> &amount) {
	Mat4<T> mat;
	mat[0][0] = amount.x;
	mat[1][1] = amount.y;
	mat[2][2] = amount.z;
	mat[3][3] = 1;
	return mat;
}

template <typename T>
Mat4<T> Mat4<T>::Translation(const Vec3<T> &amount) {
	Mat4<T> mat(1);
	mat[0][3] = amount.x;
	mat[1][3] = amount.y;
	mat[2][3] = amount.z;
	return mat;
}

template <typename T>
Mat4<T> Mat4<T>::Ortho(T left, T right, T bottom, T top, T near, T far) {
	Mat4<T> mat;
	mat[0][0] = 2.0f / (right - left);
	mat[1][1] = 2.0f / (top - bottom);
	mat[2][2] = 2.0f / (near - far);
	mat[0][3] = (right + left) / (left - right);
	mat[1][3] = (top + bottom) / (bottom - top);
	mat[2][3] = (far + near) / (far - near);
	mat[3][3] = 1;
	return mat;
}

template <typename T>
Mat4<T> Mat4<T>::Perspective(T fov, T aspectRatio, T near, T far) {
    Mat4<T> mat;
    float t = tanf(toRadians(fov) / 2);
    mat[0][0] = 1.0f / (aspectRatio * t);
    mat[1][1] = 1.0f / t;
    mat[2][2] = -(far + near) / (far - near);
    mat[3][2] = -1;
    mat[2][3] = -(2.0f * far * near) / (far - near);
    return mat;
}

template <typename T>
Mat4<T> operator+(const Mat4<T> &first, const Mat4<T> &second) {
	Mat4<T> res;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			res[i][j] = first[i][j] + second[i][j];
		}
	}
	return res;
}

template <typename T>
Mat4<T> operator-(const Mat4<T> &first, const Mat4<T> &second) {
	Mat4<T> res;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			res[i][j] = first[i][j] - second[i][j];
		}
	}
	return res;
}

template <typename T>
Mat4<T> operator*(const Mat4<T> &first, const Mat4<T> &second) {
	Mat4<T> res;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			T sum = 0;
			for (int k = 0; k < 4; ++k) {
				sum += first[i][k] * second[k][j];
			}
			res[i][j] = sum;
		}
	}
	return res;
}

template <typename T>
Vec4<T> operator*(const Mat4<T> &mat, const Vec4<T> &vec) {
	Vec4<T> res;
	for (int i = 0; i < 4; ++i) {
		T sum = 0;
		for (int k = 0; k < 4; ++k) {
			sum += mat[i][k] * vec[k];
		}
		res[i] = sum;
	}
	return res;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Mat4<T> &mat) {
	std::cout << "Mat4:" << '\n';
	for (int i = 0; i < 4; ++i) {
		std::cout << '(';
		for (int j = 0; j < 3; ++j) {
			std::cout << mat[i][j] << ", ";
		}
		std::cout << mat[i][3] << ")\n";
	}
	return os;
}

template <typename T>
Mat4<T>::Mat4() {
	memset(elements, 0, sizeof(elements));
}

template <typename T>
Mat4<T>::Mat4(T diag) {
	memset(elements, 0, sizeof(elements));
	for (int i = 0; i < 4; ++i) {
		elements[i][i] = diag;
	}
}

} // namespace renderel::math

#endif // MATH_MAT4_HPP
