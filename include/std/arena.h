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
        Arena(usize capacity);
        Arena(Allocator allocator);

        /// Get the Allocator of this arena 
        Allocator allocator();

        /// Get the amount of bytes allocated using this arena 
        /// (not the internal buffers' size).
        usize allocation();

        /// Free the internal buffers. Invalidates the arena.
        void deinit();
    };
}
