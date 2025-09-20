#pragma once
#include "cx/slice.h"
#include "cx/mem.h"

namespace cx::mem {
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
        __forceinline T* create() {
            return alloc<T>(1).ptr;
        }

        template <typename T>
        T* create(T value) {
            auto ptr = create<T>();
            *ptr = value;

            return ptr;
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

    /// General purpose allocator, used by default in data structures (wraps malloc).
    extern Allocator gpa;

    template <typename T>
    inline Slice<T> alloc(
        usize len,
        usize alignment = alignof(T)
    ) {
        return gpa.alloc<T>(len, alignment);
    }

    template <typename T>
    inline Slice<T> realloc(
        Slice<T> slice,
        usize newLen,
        usize alignment = alignof(T)
    ) {
        return gpa.realloc(slice, newLen, alignment);
    }

    template <typename T>
    inline void free(Slice<T> slice) {
        gpa.free(slice);
    }
}
