#include "cx/nums.h"

namespace cx::math {
    inline const f32 PI = 3.14159265359f;

    template <typename T>
    inline T min(T a, T b) {
        return a < b ? a : b;
    }

    template <typename T>
    inline T max(T a, T b) {
        return a > b ? a : b;
    }

    template <typename T>
    inline T clamp(T value, T min, T max) {
        return value < min ? min : ((value > max) ? max : value);
    }

    template <typename T>
    inline T lerp(T a, T b, f32 t) {
        return a + (T)((b - a) * t);
    }

    template <typename T>
    inline T lerp(T a, T b, f64 t) {
        return a + (T)((b - a) * t);
    }

    f32 sin(f32 x);
    f64 sin(f64 x);

    f32 cos(f32 x);
    f64 cos(f64 x);

    template <typename T>
    constexpr T minInt();

    template <typename T>
    constexpr T maxInt();
}
