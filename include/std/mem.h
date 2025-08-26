#pragma once
#include "std/slice.h"
#include "assert.h"

namespace std {
    template <typename T>
    void memcpy(Slice<T> dst, Slice<const T> src) {
        assert(src.len == dst.len);
        memcpy(dst.ptr, src.ptr, dst.len * sizeof(T));
    }

    template <typename T>
    bool eql(Slice<const T> lhs, Slice<const T> rhs) {
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
    inline Slice<u8> asBytes(T* ptr) {
        return { ptr, sizeof(T) };
    }

    inline bool isValidAlignment(usize alignment) {
        return alignment > 0 && (alignment & (alignment - 1)) == 0;
    }

    template <typename T>
    inline T* alignBackward(T* ptr, usize alignment) {
        assert(isValidAlignment(alignment));
        return (T*)((usize)ptr & ~(alignment - 1));
    }

    template <typename T>
    inline T* alignForward(T* ptr, usize alignment) {
        return alignBackward(ptr + (alignment - 1), alignment);
    }
}
