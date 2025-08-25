#include <std/arena.h>
#include <std/defer.h>

TEST_CASE("std::Arena should allocate with correct alignment", "[arena]") {
    std::Arena arena;
    defer { arena.deinit(); };

    auto allocator = arena.allocator();

    auto buf1 = allocator.alloc<u32>(20);
    REQUIRE((usize)buf1.ptr % alignof(u32) == 0);

    auto buf2 = allocator.alloc<u32>(30, alignof(u64));
    REQUIRE((usize)buf2.ptr % alignof(u64) == 0);

    auto buf3 = allocator.alloc<u8>(30, 3);
    REQUIRE((usize)buf3.ptr % 3 == 0);
}
