#include <std/alloc.h>
#include <std/defer.h>

TEST_CASE("std::alloc should allocate with correct alignment", "[alloc]") {
    auto buf1 = std::alloc<u32>(20);
    defer { std::free(buf1); };

    REQUIRE((usize)buf1.ptr % alignof(u32) == 0);

    auto buf2 = std::alloc<u32>(20, alignof(u64));
    defer { std::free(buf2); };

    REQUIRE((usize)buf2.ptr % alignof(u64) == 0);
}
