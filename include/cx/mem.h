#pragma once

#include "cx/slice.h"
#include "cx/assert.h"

namespace cx::mem {
    /// Copies memory from `src` to `dst`.
    /// Asserts that the lengths match.
    template <typename T>
    void copy(Slice<T> dst, Slice<const T> src) {
        ASSERT(src.len == dst.len);
#if defined(_MSC_VER) && !defined(__clang__) // MSVC
        memcpy(dst.ptr, src.ptr, dst.len * sizeof(T));
#else // GCC, Clang
        __builtin_memcpy(dst.ptr, src.ptr, dst.len * sizeof(T));
#endif
    }

    /// Compares elements of `lhs` and `rhs`.
    /// Returns early if the lengths differ.
    template <typename T>
    bool eql(Slice<const T> lhs, Slice<const T> rhs) {
        if (lhs.len != rhs.len) return false;
        for (usize i = 0; i < lhs.len; i++) {
            if (lhs[i] != rhs[i]) return false;
        }

        return true;
    }

    /// Compares elements of `lhs` and `rhs` until the sentinel value.
    /// Useful for comparing null terminated strings.
    template <typename T, T sentinel = 0>
    bool eqlSentinel(T const* lhs, T const* rhs) {
        while (true) {
            T l = *lhs;
            T r = *rhs;
            if (l != r) return false;
            if (l == sentinel) return true;

            lhs += 1;
            rhs += 1;
        }
    }

    /// Converts a pointer of any type to a slice of bytes.
    template <typename T>
    inline Slice<u8> asBytes(T* ptr) {
        return { ptr, sizeof(T) };
    }

    /// Returns true if the alignment is 2^x and greater than 0.
    inline bool isValidAlignment(usize alignment) {
        return alignment > 0 && (alignment & (alignment - 1)) == 0;
    }

    /// Returns the nearest smaller than `ptr` pointer with specified `alignment`.
    /// Asserts that the alignment is valid.
    template <typename T>
    inline T* alignBackward(T* ptr, usize alignment) {
        ASSERT(isValidAlignment(alignment));
        return (T*)((usize)ptr & ~(alignment - 1));
    }

    /// Returns the nearest bigger than `ptr` pointer with specified `alignment`.
    /// Asserts that the alignment is valid.
    template <typename T>
    inline T* alignForward(T* ptr, usize alignment) {
        return alignBackward(ptr + (alignment - 1), alignment);
    }

    /// Returns the memory of `value` as a different type. 
    template <typename T, typename U>
    T bitCast(U value) {
        static_assert(sizeof(T) == sizeof(U));

        T out;
#if defined(_MSC_VER) && !defined(__clang__) // MSVC
        memcpy(&out, &value, sizeof(T));
#else // GCC, Clang
        __builtin_memcpy(&out, &value, sizeof(T));
#endif

        return out;
    }
}
