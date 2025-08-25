#pragma once
#include "std/alloc.h"

namespace std {
    struct Arena {
        struct Page {
            Page* previous;
            usize len;
            usize capacity;
            u8 bytes;
        };

        Allocator parentAllocator;
        Page* page;

        Arena();
        Arena(Allocator allocator);

        Allocator allocator();
        void deinit();
    };
}
