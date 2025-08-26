#include "std/alloc.h"
#include <stdlib.h>

namespace std {
    static Slice<u8> cAlloc(void*, usize len, usize alignment) {
        u8* ptr = (u8*)_aligned_malloc(len, alignment); 
        assert(ptr != nullptr);

        return { ptr, len };
    }

    static Slice<u8> cRealloc(void*, Slice<u8> slice, usize newLen, usize alignment) {
        auto ptr = (u8*)_aligned_realloc(slice.ptr, newLen, alignment);
        assert(ptr != nullptr);

        return { ptr, newLen };
    }

    static void cFree(void*, Slice<u8> slice) {
        ::_aligned_free(slice.ptr);
    }

    Allocator cAllocator = {
        .ptr = nullptr,
        .allocFn = &cAlloc,
        .reallocFn = &cRealloc,
        .freeFn = &cFree,
    };
}
