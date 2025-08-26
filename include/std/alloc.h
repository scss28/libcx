#pragma once
#include "std/slice.h"
#include "std/mem.h"

namespace std {
    struct Allocator {
        using Alloc = Slice<u8>(*)(void*, usize len, usize alignment);
        using Realloc = Slice<u8>(*)(void*, Slice<u8> slice, usize len, usize alignment);
        using Free = void(*)(void*, Slice<u8> slice);

        void* ptr;
        Alloc allocFn;
        Realloc reallocFn;
        Free freeFn;

        template <typename T>
        Slice<T> alloc(
            usize len,
            usize alignment = alignof(T)
        ) {
            isValidAlignment(alignment);

            auto bytes = allocFn(ptr, len * sizeof(T), alignment); 
            return { (T*)bytes.ptr, len };
        }

        template <typename T>
        Slice<T> realloc(
            Slice<T> slice,
            usize newLen,
            usize alignment = alignof(T)
        ) {
            isValidAlignment(alignment);

            if (slice.len == 0) {
                return alloc<T>(newLen, alignment);
            }

            auto bytes = reallocFn(ptr, slice, newLen * sizeof(T), alignment);
            return { (T*)bytes.ptr, newLen };
        }

        template <typename T>
        void free(Slice<T> slice) {
            freeFn(ptr, {(u8*)slice.ptr, slice.len * sizeof(T)});
        }
    };

    extern Allocator cAllocator;

    template <typename T>
    inline Slice<T> alloc(
        usize len,
        usize alignment = alignof(T)
    ) {
        return cAllocator.alloc<T>(len, alignment);
    }

    template <typename T>
    inline Slice<T> realloc(
        Slice<T> slice,
        usize newLen,
        usize alignment = alignof(T)
    ) {
        return cAllocator.realloc(slice, newLen, alignment);
    }

    template <typename T>
    inline void free(Slice<T> slice) {
        cAllocator.free(slice);
    }
}
