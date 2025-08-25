#pragma once
#include "std/slice.h"
#include "assert.h"

namespace std {
    template <typename T>
    void memcpy(Buf<T> dst, Slice<T> src) {
        assert(src.len == dst.len);
        for (usize i = 0; i < src.len; i++) {
            dst[i] = src[i];
        }
    }

    template <typename T>
    bool eql(Slice<T> lhs, Slice<T> rhs) {
        if (lhs.len != rhs.len) return false;
        for (usize i = 0; i < lhs.len; i++) {
            if (lhs[i] != rhs[i]) return false;
        }

        return true;
    }

    template <typename T, T sentinel = 0>
    bool eqlZ(T const* lhs, T const* rhs) {
        while (true) {
            T l = *lhs;
            T r = *rhs;
            if (l != r) return false;
            if (l == sentinel) return true;

            lhs += 1;
            rhs += 1;
        }
    }

    template <typename T>
    Buf<u8> asBytes(T* ptr) {
        return { ptr, sizeof(T) };
    }

    template <typename T>
    void setZeros(T* ptr) {
        for (u8* byte : asBytes(ptr)) {
            *byte = 0;
        }
    }

    template <typename T>
    constexpr T zeros() {
        T value;
        setZeros(&value);

        return value;
    }
}
