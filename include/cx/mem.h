#pragma once

#include "cx/slice.h"
#include "cx/assert.h"

#ifdef _MSC_VER
#include <memory.h>
#endif

namespace cx::mem {
    /// Converts a pointer of any type to a slice of bytes.
    template <typename T>
    __forceinline Slice<u8> asBytes(T* ptr) {
        return { (u8*)ptr, sizeof(T) };
    }

    /// Copies memory from `src` to `dst`.
    /// Asserts that the lengths match.
    template <typename T>
    void copy(Slice<T> dst, Slice<const T> src) {
        ASSERT(src.len == dst.len);
#ifdef _MSC_VER
        memcpy(dst.ptr, src.ptr, dst.len * sizeof(T));
#else // GCC, Clang
        __builtin_memcpy(dst.ptr, src.ptr, dst.len * sizeof(T));
#endif
    }

    /// Returns the memory of `value` as a different type. 
    template <typename T, typename F>
    T bitCast(F from) {
        static_assert(sizeof(T) == sizeof(F));

        T out;
        copy<u8>(asBytes(&out), asBytes(&from));

        return out;
    }

    /// Sets each element in `dst` to `value`.
    template <typename T>
    void set(Slice<T> dst, T value) {
        for (T* item : dst) *item = value;
    }

    /// Sets each element in `dst` to `value`.
    template <typename T>
    void set(Slice<T> dst, T value) requires (sizeof(T) == sizeof(int)) {
#ifdef _MSC_VER
        memset(dst.ptr, bitCast(value), dst.len);
#else // GCC, Clang
        __builtin_memset(dst.ptr, bitCast(value), dst.len);
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
    template <typename T, T Sentinel = 0>
    bool eqlSentinel(T const* lhs, T const* rhs) {
        while (true) {
            T l = *lhs;
            T r = *rhs;
            if (l != r) return false;
            if (l == Sentinel) return true;

            lhs += 1;
            rhs += 1;
        }
    }

    /// Returns true if the alignment is 2^x and greater than 0.
    inline bool isValidAlignment(usize alignment) {
        return alignment > 0 && (alignment & (alignment - 1)) == 0;
    }

    /// Returns the nearest smaller than `ptr` pointer with specified `alignment`.
    /// Asserts that the alignment is valid.
    template <typename T>
    T* alignBackward(T* ptr, usize alignment) {
        ASSERT(isValidAlignment(alignment));
        return (T*)((usize)ptr & ~(alignment - 1));
    }

    /// Returns the nearest bigger than `ptr` pointer with specified `alignment`.
    /// Asserts that the alignment is valid.
    template <typename T>
    __forceinline T* alignForward(T* ptr, usize alignment) {
        return alignBackward(ptr + (alignment - 1), alignment);
    }

    template <typename T, T Sentinel = 0>
    Slice<T> sliceTo(T* ptr) {
        T* end = ptr;
        while (*end != Sentinel) end += 1;

        usize len = end - ptr;
        return {ptr, len};
    }
}
