#include "cx/slice.h"
#include "cx/alloc.h"
#include "cx/defer.h"
#include "cx/mem.h"

namespace cx {
    template <typename T>
    struct ArrayList {
        Slice<T> items;
        usize capacity = 0;

        /// Free all allocated memory. Invalidates this `ArrayList`.
        void deinit(mem::Allocator allocator = mem::cAllocator) {
            items.len = capacity;
            allocator.free(items);

            *this = {0};
        }

        void resize(usize newCapacity, mem::Allocator allocator = mem::cAllocator) {
            capacity = newCapacity;

            usize oldItemsLen = items.len;
            items = allocator.realloc(items, capacity);
            items.len = oldItemsLen;
        }

        void ensureCapacity(usize atLeast, mem::Allocator allocator = mem::cAllocator) {
            if (atLeast <= capacity) return;
            
            usize newCapacity = capacity;
            while (true) {
                newCapacity += newCapacity / 2 + 1;
                if (newCapacity >= atLeast) break;
            }

            resize(newCapacity, allocator);
        }

        inline void ensureUnusedCapacity(
            usize atLeast, 
            mem::Allocator allocator = mem::cAllocator
        ) {
            ensureCapacity(items.len + atLeast, allocator);
        }

        void push(T value, mem::Allocator allocator = mem::cAllocator) {
            if (capacity == items.len) {
                resize((capacity + 1) * 2, allocator);
            }

            items.len += 1;
            items[items.len - 1] = value;
        }

        void pushMany(Slice<const T> slice) {
            if (slice.len == 0) return;
            ensureUnusedCapacity(slice.len);

            items.len += slice.len;
            memcpy(items[items.len - slice.len, items.len], slice);
        }

        T pop() {
            assert(items.len > 0);

            defer { items.len -= 1; };
            return items[items.len - 1];
        }

        inline void clear() {
            items.len = 0;
        }
    };
}
