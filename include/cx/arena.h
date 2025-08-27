#pragma once
#include "cx/alloc.h"

namespace cx {
    struct Arena {
        struct Page {
            Page* previous;
            usize len;
            usize capacity;
            u8 bytes;
        };

        mem::Allocator parentAllocator;
        Page* page;

        Arena();
        Arena(usize capacity);
        Arena(mem::Allocator allocator);

        /// Get the Allocator of this arena 
        mem::Allocator allocator();

        /// Get the amount of bytes allocated using this arena 
        /// (not the internal buffers' size).
        usize allocation();

        /// Free the internal buffers. Invalidates the arena.
        void deinit();
    };
}
