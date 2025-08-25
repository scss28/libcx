#include "std/alloc.h"
#include <stdlib.h>

namespace std {
    struct CAllocatorVTable {
        static Buf<u8> alloc(void*, usize len, usize alignment) {
            u8* ptr = (u8*)_aligned_malloc(len, alignment); 
            return { ptr, len };
        }

        static void realloc(void*, Buf<u8>* buf, usize newLen, usize alignment) {
            buf->ptr = (u8*)_aligned_realloc(buf->ptr, newLen, alignment);
            buf->len = newLen;
        }

        static void free(void*, Buf<u8> buf) {
            ::_aligned_free(buf.ptr);
        }
    };

    Allocator cAllocator = {
        .ptr = nullptr,
        .allocFn = &CAllocatorVTable::alloc,
        .reallocFn = &CAllocatorVTable::realloc,
        .freeFn = &CAllocatorVTable::free,
    };
}
