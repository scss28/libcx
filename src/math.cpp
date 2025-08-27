#include "cx/math.h"

namespace cx::math {
    template <>
    constexpr u8 maxInt() {
        return 0xff;
    }

    template <>
    constexpr u8 minInt() {
        return 0;
    }

    template <>
    constexpr u16 maxInt() {
        return 0xffff;
    }

    template <>
    constexpr u16 minInt() {
        return 0;
    }

    template <>
    constexpr u32 maxInt() {
        return 0xffffffff;
    }

    template <>
    constexpr u32 minInt() {
        return 0;
    }

    template <>
    constexpr u64 maxInt() {
        return 0xffffffffffffffff;
    }

    template <>
    constexpr u64 minInt() {
        return 0;
    }

    template <>
    constexpr i8 maxInt() {
        return 0x7f;
    }

    template <>
    constexpr i8 minInt() {
        return 0x80;
    }

    template <>
    constexpr i16 maxInt() {
        return 0x7fff;
    }

    template <>
    constexpr i16 minInt() {
        return 0x8000;
    }

    template <>
    constexpr i32 maxInt() {
        return 0x7fffffff;
    }

    template <>
    constexpr i32 minInt() {
        return 0x80000000;
    }

    template <>
    constexpr i64 maxInt() {
        return 0x7fffffffffffffff;
    }

    template <>
    constexpr i64 minInt() {
        return 0x8000000000000000;
    }

#ifdef INT128
    template <>
    constexpr u128 maxInt() {
        return maxInt<u64>() | ((u128)maxInt<u64>() >> 64);
    }

    template <>
    constexpr u128 minInt() {
        return 0;
    }

    template <>
    constexpr i128 maxInt() {
        return maxInt<i64>() | ((i128)maxInt<u64>() >> 64);
    }

    template <>
    constexpr i128 minInt() {
        return (i128)maxInt<u128>() << 127;
    }
#endif
}
