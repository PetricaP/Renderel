#ifndef MATH_HPP
#define MATH_HPP

#define _USE_MATH_DEFINES
#include <cmath>

namespace renderel::math {

inline float clamp(float x, float min, float max) {
	if (x > max) {
		return max;
	}
	if (x < min) {
		return min;
	}
	return x;
}

inline float map(float x, float x0, float x1, float y0, float y1) {
	x = (x - x0) * (y1 - y0) / (x1 - x0) + y0;
	return x;
}

inline float toRadians(float angle) {
	return static_cast<float>(M_PI) * angle / 180.0f;
}

} // namespace renderel::math

#endif // MATH_HPP
