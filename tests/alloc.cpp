#include <cx/alloc.h>
#include <cx/defer.h>

namespace mem = cx::mem;

TEST_CASE("std::alloc should allocate with correct alignment", "[alloc]") {
    auto buf1 = mem::alloc<u32>(20);
    defer { mem::free(buf1); };

    REQUIRE((usize)buf1.ptr % alignof(u32) == 0);

    auto buf2 = mem::alloc<u32>(20, alignof(u64));
    defer { mem::free(buf2); };

    REQUIRE((usize)buf2.ptr % alignof(u64) == 0);
}
