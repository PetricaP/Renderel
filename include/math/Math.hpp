#ifndef MATH_HPP
#define MATH_HPP

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

} // namespace renderel::math

#endif // MATH_HPP
