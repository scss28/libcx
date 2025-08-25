#include "std/slice.h"
#include "std/alloc.h"
#include "std/defer.h"
#include "std/mem.h"

namespace std {
    template <typename T>
    struct ArrayList {
        Buf<T> items;
        usize capacity = 0;

        void deinit(Allocator* allocator = &cAllocator) {
            items.len = capacity;
            free(items, allocator);

            std::setZeros(this);
        }

        void resize(usize newCapacity, Allocator allocator = cAllocator) {
            capacity = newCapacity;

            usize oldItemsLen = items.len;
            realloc<T>(&items, capacity, allocator);
            items.len = oldItemsLen;
        }

        void ensureCapacity(usize atLeast, Allocator allocator = cAllocator) {
            if (atLeast <= capacity) return;
            
            usize newCapacity = capacity;
            while (true) {
                newCapacity += newCapacity / 2 + 1;
                if (newCapacity >= atLeast) break;
            }

            resize(newCapacity);
        }

        void ensureUnusedCapacity(usize atLeast, Allocator allocator = cAllocator) {
            ensureCapacity(items.len + atLeast);
        }

        void push(T value, Allocator allocator = cAllocator) {
            if (capacity == items.len) {
                resize((capacity + 1) * 2, allocator);
            }

            items.len += 1;
            items[items.len - 1] = value;
        }

        void pushMany(Slice<T> slice) {
            if (slice.len == 0) return;
            ensureUnusedCapacity(slice.len);

            items.len += slice.len;
            std::memcpy(items[items.len - slice.len, items.len], slice);
        }

        T pop() {
            assert(items.len > 0);

            defer { items.len -= 1; };
            return items[items.len - 1];
        }
    };
}
