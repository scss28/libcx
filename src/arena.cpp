#include "cx/arena.h"
#include "cx/mem.h"

namespace cx {
    Arena::Page* allocateNewPage(
        Arena::Page* previous, 
        mem::Allocator allocator,
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

    Arena::Arena() : Arena(mem::gpa) {}
    Arena::Arena(usize capacity) : Arena() {
        page = allocateNewPage(nullptr, parentAllocator, capacity);
    }

    Arena::Arena(mem::Allocator allocator) : parentAllocator(allocator), page(nullptr) {}

    void Arena::deinit() {
        while (page != nullptr) {
            Arena::Page* previous = page->previous;
            parentAllocator.free<u8>({(u8*)page, page->capacity + sizeof(usize) * 3});
            page = previous;
        }

        *this = {0};
    }

    Slice<u8> arenaAlloc(void* p, usize len, usize alignment) {
        Arena* arena = (Arena*)p;
        if (arena->page == nullptr) {
            arena->page = allocateNewPage(
                nullptr, 
                arena->parentAllocator, 
                4096 - sizeof(usize) * 3
            );
        }

        u8* ptr = mem::alignForward(&arena->page->bytes + arena->page->len, alignment);
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

    Slice<u8> arenaRealloc(void* p, Slice<u8> slice, usize newLen, usize alignment) {
        Arena* arena = (Arena*)p;
        if (arena->page != nullptr) {
            if (
                &arena->page->bytes + arena->page->len - slice.len == slice.ptr
                && slice.ptr + newLen <= &arena->page->bytes + arena->page->capacity
            ) {
                return {slice.ptr, newLen};
            }
        }

        return arenaAlloc(p, newLen, alignment);
    }

    void arenaFree(void* p, Slice<u8> slice) {
        Arena* arena = (Arena*)p;
        if (arena->page == nullptr) return;

        // Free can only happen if 'slice' is the last allocated thing.
        if (&arena->page->bytes + arena->page->len - slice.len == slice.ptr) {
            arena->page->len -= slice.len;
        }
    }

    mem::Allocator Arena::allocator() {
        return {
            .ptr = this,
            .allocFn = &arenaAlloc,
            .reallocFn = &arenaRealloc,
            .freeFn = &arenaFree,
        };
    }

    usize Arena::allocation() {
        usize count = 0;
        if (page != nullptr) {
            count += page->len;
            
            Arena::Page* currentPage = page->previous;
            while (currentPage != nullptr) {
                count += currentPage->capacity;
                currentPage = currentPage->previous;
            }
        }

        return count;
    }
}
