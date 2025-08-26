#include <std/arena.h>
#include <std/defer.h>

TEST_CASE("Arena should allocate with correct alignment", "[arena]") {
    std::Arena arena;
    defer { arena.deinit(); };

    auto allocator = arena.allocator();

    auto slice1 = allocator.alloc<u32>(20);
    auto slice2 = allocator.alloc<u32>(30, alignof(u64));
    auto slice3 = allocator.alloc<u8>(30, 8);

    REQUIRE((usize)slice1.ptr % alignof(u32) == 0);
    REQUIRE((usize)slice2.ptr % alignof(u64) == 0);
    REQUIRE((usize)slice3.ptr % 8 == 0);
}

TEST_CASE("Arena should free the last allocated buffer", "[arena]") {
    std::Arena arena;
    defer { arena.deinit(); };

    auto allocator = arena.allocator();

    auto slice = allocator.alloc<u8>(20);
    allocator.free(slice);

    REQUIRE(arena.allocation() == 0);
}

TEST_CASE("Arena should resize the last allocated buffer", "[arena]") {
    std::Arena arena(20);
    defer { arena.deinit(); };

    auto allocator = arena.allocator();

    auto initialSlice = allocator.alloc<u8>(10);
    auto reallocSlice = allocator.realloc(initialSlice, 20);
    REQUIRE(initialSlice.ptr == reallocSlice.ptr);
}
