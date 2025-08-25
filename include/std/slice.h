#pragma once
#include "std/nums.h"

#include <assert.h>

namespace std {
    template <typename T>
    struct Buf {
        T* ptr; 
        usize len;

        Buf() : ptr(nullptr), len(0) {}
        Buf(T* ptr, usize len) : ptr(ptr), len(len) {}
        Buf(u8* cstring) : ptr(cstring) {
            u8* end = ptr;
            while (*end != 0) end += 1;

            len = end - ptr;
        }

        template <typename T2>
        Buf(Buf<T2> buf) : ptr(buf.ptr) {
            // Shouldnt be possible to go from lower to higher alignment,
            // 'from' alignment needs to be divisible by the 'to' alignment.
            // u16 -> u8 | u8 -x> u16
            static_assert(
                alignof(T) > alignof(T2)
                && alignof(T2) % alignof(T) == 0 
            );
            assert((buf.len * sizeof(T2)) % sizeof(T) == 0);
            len = buf.len * sizeof(T2) / sizeof(T);
        }

        inline T& operator[](usize index) const {
            assert(index < len);
            return ptr[index];
        }

        inline Buf<T> operator[](usize start, usize end) const {
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

    template <typename T>
    struct Slice {
        T const* ptr = nullptr; 
        usize len = 0;

        Slice() : ptr(nullptr), len(0) {}
        Slice(T* ptr, usize len) : ptr(ptr), len(len) {}
        Slice(u8 const* cstring) : ptr(cstring) {
            u8 const* end = ptr;
            while (*end != 0) end += 1;

            len = end - ptr;
        }

        template <typename T2>
        Slice(Slice<T2> slice) : ptr(slice.ptr) {
            // Shouldnt be possible to go from lower to higher alignment,
            // 'from' alignment needs to be divisible by the 'to' alignment.
            // u16 -> u8 | u8 -x> u16
            static_assert(
                alignof(T) > alignof(T2)
                && alignof(T2) % alignof(T) == 0 
            );
            assert((slice.len * sizeof(T2)) % sizeof(T) == 0);
            len = slice.len * sizeof(T2) / sizeof(T);
        }

        Slice(Buf<T> buf) : ptr(buf.ptr), len(buf.len) {}

        inline T const& operator[](usize index) const {
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
