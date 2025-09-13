#include "cx/alloc.h"
#include <stdlib.h> // @libc

namespace cx::mem {
    static Slice<u8> gpaAlloc(void*, usize len, usize alignment) {
        u8* ptr = (u8*)_aligned_malloc(len, alignment); 
        ASSERT(ptr != nullptr);

        return { ptr, len };
    }

    static Slice<u8> gpaRealloc(void*, Slice<u8> slice, usize newLen, usize alignment) {
        auto ptr = (u8*)_aligned_realloc(slice.ptr, newLen, alignment);
        ASSERT(ptr != nullptr);

        return { ptr, newLen };
    }

    static void gpaFree(void*, Slice<u8> slice) {
        ::_aligned_free(slice.ptr);
    }

    Allocator gpa = {
        .ptr = nullptr,
        .allocFn = &gpaAlloc,
        .reallocFn = &gpaRealloc,
        .freeFn = &gpaFree,
    };
}
