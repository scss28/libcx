#include "cx/nums.h"
#include <math.h>

namespace cx::math {
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
    inline T sin(T x) {
        return ::sin(x);
    }

    template <typename T>
    inline T cos(T x) {
        return ::cos(x);
    }

    template <typename T>
    constexpr T minInt();

    template <typename T>
    constexpr T maxInt();
}
