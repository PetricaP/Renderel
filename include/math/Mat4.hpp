#ifndef MATH_MAT4_HPP
#define MATH_MAT4_HPP

#include "math/Vec3.hpp"
#include "math/Vec4.hpp"
#include <cstring>
#include <iostream>

namespace renderel::math {

template <typename T>
union Mat4 {
	T elements[4][4];
	Vec4<T> vecs[4];

	Mat4();
	Mat4(T diag);

	Vec4<T> operator[](unsigned int index) const;
	Vec4<T> &operator[](unsigned int index);

	static Mat4 Ortho(T right, T left, T top, T bottom, T near, T far);
    static Mat4 Translation(const Vec3<T> &vec);
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
Mat4<T> Mat4<T>::Translation(const Vec3<T> &vec) {
    Mat4<T> mat(1);
    mat[0][3] = vec.x;
    mat[1][3] = vec.y;
    mat[2][3] = vec.z;
    return mat;
}

template <typename T>
Mat4<T> Mat4<T>::Ortho(T left, T right, T bottom, T top, T near, T far) {
	Mat4<T> mat(1);
	mat[0][0] = 2.0f / (right - left);
	mat[1][1] = 2.0f / (top - bottom);
    mat[2][2] = 2.0f / (near - far);
    mat[0][3] = (right + left) / (left - right);
    mat[1][3] = (top + bottom) / (bottom - top);
    mat[2][3] = (far + near) / (far - near);
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
