#pragma once

#include "cx/nums.h"

namespace cx::math {
    inline const f32 PI = 3.14159265359f;

    template <typename T>
    __forceinline T min(T a, T b) {
        return a < b ? a : b;
    }

    template <typename T>
    __forceinline T max(T a, T b) {
        return a > b ? a : b;
    }

    template <typename T>
    T clamp(T value, T min, T max) {
        return value < min ? min : ((value > max) ? max : value);
    }

    template <typename T>
    __forceinline T lerp(T a, T b, f32 t) {
        return a + (T)((b - a) * t);
    }

    template <typename T>
    __forceinline T lerp(T a, T b, f64 t) {
        return a + (T)((b - a) * t);
    }

    f32 sqrt(f32 x);
    f64 sqrt(f64 x);

    f32 sin(f32 x);
    f64 sin(f64 x);

    f32 cos(f32 x);
    f64 cos(f64 x);

    template <typename T>
    constexpr T minInt();

    template <typename T>
    constexpr T maxInt();

    template <typename T>
    constexpr T zero() {
        return 0;
    }

    template <typename T>
    concept HasZero = requires { 
        { T::zero() };
    };

    template <HasZero T>
    constexpr T zero() {
        return T::zero;
    }

    template <typename T>
    constexpr T one() {
        return 1;
    }

    template <typename T>
    concept HasOne = requires { 
        { T::One };
    };

    template <HasOne T>
    constexpr T one() {
        return T::one();
    }
}
