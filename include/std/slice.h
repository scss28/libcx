#pragma once
#include "std/nums.h"
#include <assert.h>

namespace std {
    template <typename T>
    struct Slice {
        T* ptr = nullptr; 
        usize len = 0;

        Slice() : ptr(nullptr), len(0) {}
        Slice(T* ptr, usize len) : ptr(ptr), len(len) {}
        Slice(u8 const* cstring) : ptr(cstring) {
            u8 const* end = ptr;
            while (*end != 0) end += 1;

            len = end - ptr;
        }

        template <typename U>
        Slice(Slice<U> slice) : ptr(slice.ptr) {
            // Shouldnt be possible to go from lower to higher alignment,
            // 'from' alignment needs to be divisible by the 'to' alignment.
            // u16 -> u8 | u8 -x> u16
            static_assert(
                alignof(T) > alignof(U)
                && alignof(U) % alignof(T) == 0 
            );
            assert((slice.len * sizeof(U)) % sizeof(T) == 0);
            len = slice.len * sizeof(U) / sizeof(T);
        }

        inline T& operator[](usize index) const {
            assert(index < len);
            return ptr[index];
        }

        inline Slice<T> operator[](usize start, usize end) const {
            assert(end >= start);
            assert(end <= len);
            return { ptr + start, end - start };
        }

        T* begin() const {
            return ptr;
        }

        T* end() const { 
            return ptr + len;
        }
    };
}
