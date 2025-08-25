#pragma once
#include "std/slice.h"

namespace std {
    struct Allocator {
        using Alloc = Buf<u8>(*)(void*, usize len, usize alignment);
        using Realloc = void(*)(void*, Buf<u8>* buf, usize len, usize alignment);
        using Free = void(*)(void*, Buf<u8> buf);

        void* ptr;
        Alloc allocFn;
        Realloc reallocFn;
        Free freeFn;

        template <typename T>
        Buf<T> alloc(
            usize len,
            usize alignment = alignof(T)
        ) {
            auto bytes = allocFn(ptr, len * sizeof(T), alignment); 
            return { (T*)bytes.ptr, len };
        }

        template <typename T>
        void realloc(
            Buf<T>* buf,
            usize newLen,
            usize alignment = alignof(T)
        ) {
            if (buf->len == 0) {
                *buf = alloc<T>(newLen, alignment);
                return;
            }

            buf->ptr = (T*)reallocFn(buf, newLen * sizeof(T), alignment).ptr;
            buf->len = newLen;
        }

        template <typename T>
        void free(Buf<T> buf) {
            freeFn(ptr, {(u8*)buf.ptr, buf.len * sizeof(T)});
        }
    };

    extern Allocator cAllocator;

    template <typename T>
    inline Buf<T> alloc(
        usize len,
        usize alignment = alignof(T)
    ) {
        return cAllocator.alloc<T>(len, alignment);
    }

    template <typename T>
    inline void realloc(
        Buf<T>* buf,
        usize newLen,
        usize alignment = alignof(T)
    ) {
        cAllocator.realloc(buf, newLen, alignment);
    }

    template <typename T>
    inline void free(Buf<T> buf) {
        cAllocator.free(buf);
    }
}
