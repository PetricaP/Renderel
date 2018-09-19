#ifndef MATH_MAT4_HPP
#define MATH_MAT4_HPP

#include "math/Math.hpp"
#include "math/Vec3.hpp"
#include "math/Vec4.hpp"
#include <cstring>
#include <iostream>

namespace renderel::math {

template <typename T = float>
union Mat4 {
	T elements[4][4];
	Vec4<T> vecs[4];

	Mat4();
	Mat4(T diag);
	Mat4(const Vec4<T> &row0, const Vec4<T> &row1, const Vec4<T> &row2,
		 const Vec4<T> &row3);

	Vec4<T> operator[](unsigned int index) const;
	Vec4<T> &operator[](unsigned int index);

	static Mat4 Ortho(T left, T right, T bottom, T top, T near, T far);
	static Mat4 Perspective(T fov, T aspectRatio, T near, T far);
	static Mat4 SimplePerspective(T aspectRatio);
	static Mat4 Translation(const Vec3<T> &amount);
	static Mat4 Scale(const Vec3<T> &scale);
	static Mat4 LookAt(const Vec3<T> &eye, const Vec3<T> &at,
					   const Vec3<T> &up);
	Mat4 &StripTranslation();
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
	Vec3<T> zAxis = (eye - at).Normalize();
	Vec3<T> xAxis = zAxis.Cross(up).Normalize();
	Vec3<T> yAxis = xAxis.Cross(zAxis).Normalize();

	Mat4<T> viewMatrix(
		Vec4<T>(xAxis, -xAxis.Dot(eye)), Vec4<T>(yAxis, -yAxis.Dot(eye)),
		Vec4<T>(zAxis, -zAxis.Dot(eye)), Vec4<T>(0.0f, 0.0f, 0.0f, 1.0f));

	return viewMatrix;
}

template <typename T>
Mat4<T> &Mat4<T>::StripTranslation() {
	for (auto i = 0; i < 3; ++i) {
		elements[3][i] = 0;
		elements[i][3] = 0;
	}
	elements[3][3] = 1;
	return *this;
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
	float t = 1 / tanf(toRadians(fov) / 2);
	mat[0][0] = t / aspectRatio;
	mat[1][1] = t;
	mat[2][2] = (far + near) / (near - far);
	mat[2][3] = (2.0f * far * near) / (near - far);
	mat[3][2] = -1;
	return mat;
}

template <typename T>
Mat4<T> Mat4<T>::SimplePerspective(T aspectRatio) {
	Mat4<T> view(1.0f);
	view[0][0] = 1.0f / aspectRatio;
	view[3][3] = 0.0f;
	view[3][2] = -1.0f;
	return view;
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

template <typename T>
Mat4<T>::Mat4(const Vec4<T> &row0, const Vec4<T> &row1, const Vec4<T> &row2,
			  const Vec4<T> &row3) {
	elements[0][0] = row0.x;
	elements[0][1] = row0.y;
	elements[0][2] = row0.z;
	elements[0][3] = row0.w;

	elements[1][0] = row1.x;
	elements[1][1] = row1.y;
	elements[1][2] = row1.z;
	elements[1][3] = row1.w;

	elements[2][0] = row2.x;
	elements[2][1] = row2.y;
	elements[2][2] = row2.z;
	elements[2][3] = row2.w;

	elements[3][0] = row3.x;
	elements[3][1] = row3.y;
	elements[3][2] = row3.z;
	elements[3][3] = row3.w;
}

} // namespace renderel::math

#endif // MATH_MAT4_HPP
