#pragma once

#include "cx/nums.h"
#include "cx/assert.h"

namespace cx {
    template <typename T>
    struct Slice {
        T* ptr = nullptr; 
        usize len = 0;

        Slice() : ptr(nullptr), len(0) {}
        Slice(T* ptr, usize len) : ptr(ptr), len(len) {}

        template <typename U>
        Slice(Slice<U> slice) : ptr(slice.ptr), len(slice.len) {}

        template <usize N>
        Slice(T (&arr)[N]) : ptr(arr), len(N) {}

        T& operator[](usize index) const {
            ASSERT(index < len);
            return ptr[index];
        }

        Slice<T> from(usize start) const {
            ASSERT(start < len);
            return { ptr + start, len - start };
        }

        Slice<T> to(usize end) const {
            ASSERT(end <= len);
            return { ptr, len - (len - end) };
        }

        T* begin() const {
            return ptr;
        }

        T* end() const { 
            return ptr + len;
        }
    };
}
