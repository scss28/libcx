#include "std/arena.h"

namespace std {
    Arena::Arena() : Arena(cAllocator) {}
    Arena::Arena(Allocator allocator) : parentAllocator(allocator), page(nullptr) {}

    void Arena::deinit() {
        while (page != nullptr) {
            Arena::Page* previous = page->previous;
            parentAllocator.free<u8>({(u8*)page, page->capacity + sizeof(usize) * 3});
            page = previous;
        }
    }

    Arena::Page* allocateNewPage(
        Arena::Page* previous, 
        Allocator allocator,
        usize capacity
    ) {
        Arena::Page* page = (Arena::Page*)allocator.alloc<u8>(
            capacity + sizeof(usize) * 3,
            alignof(Arena::Page)
        ).ptr;
        page->previous = previous;
        page->len = 0;
        page->capacity = capacity;

        return page;
    }

    struct ArenaVTable {
        static Buf<u8> alloc(void* p, usize len, usize alignment) {
            Arena* arena = (Arena*)p;
            if (arena->page == nullptr) {
                arena->page = allocateNewPage(
                    nullptr, 
                    arena->parentAllocator, 
                    4096 - sizeof(usize) * 3
                );
            }

            u8* ptr = &arena->page->bytes + arena->page->len;
            ptr += alignment - ((usize)ptr % alignment);

            u8* end = &arena->page->bytes + arena->page->capacity;
            if (ptr + len > end) {
                arena->page = allocateNewPage(
                    arena->page, 
                    arena->parentAllocator, 
                    len > arena->page->capacity ? len : arena->page->capacity
                );
                ptr = &arena->page->bytes;
            }

            arena->page->len = (ptr - &arena->page->bytes) + len;
            return {ptr, len};
        }

        static void realloc(void* p, Buf<u8>* buf, usize newLen, usize alignment) {
            Arena* arena = (Arena*)p;
            if (arena->page != nullptr) {
                if (
                    &arena->page->bytes + arena->page->len - buf->len == buf->ptr
                    && buf->ptr + newLen <= &arena->page->bytes + arena->page->capacity
                ) {
                    *buf = {buf->ptr, newLen};
                    return;
                }
            }

            *buf = alloc(p, newLen, alignment);
        }

        static void free(void* p, Buf<u8> buf) {
            Arena* arena = (Arena*)p;
            if (arena->page == nullptr) return;

            // Free can only happen if 'buf' is the last allocated thing.
            if (&arena->page->bytes + arena->page->len - buf.len == buf.ptr) {
                arena->page->len -= buf.len;
            }
        }
    };



    Allocator Arena::allocator() {
        return {
            .ptr = this,
            .allocFn = &ArenaVTable::alloc,
            .reallocFn = &ArenaVTable::realloc,
            .freeFn = &ArenaVTable::free,
        };
    }
}
