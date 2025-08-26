#include "std/alloc.h"
#include <stdlib.h>

namespace std {
    struct CAllocatorVTable {
        static Slice<u8> alloc(void*, usize len, usize alignment) {
            u8* ptr = (u8*)_aligned_malloc(len, alignment); 
            return { ptr, len };
        }

        static Slice<u8> realloc(void*, Slice<u8> slice, usize newLen, usize alignment) {
            auto ptr = (u8*)_aligned_realloc(slice.ptr, newLen, alignment);
            return { ptr, newLen };
        }

        static void free(void*, Slice<u8> slice) {
            ::_aligned_free(slice.ptr);
        }
    };

    Allocator cAllocator = {
        .ptr = nullptr,
        .allocFn = &CAllocatorVTable::alloc,
        .reallocFn = &CAllocatorVTable::realloc,
        .freeFn = &CAllocatorVTable::free,
    };
}
