#include <cx/either.h>
#include <cx/nums.h>

TEST_CASE("Either works", "[either]") {
    i32 i32Value = 1;
    u64 u64Value = 1;

    cx::Either<i32, u64> either = i32Value;
    REQUIRE(either.is<i32>());

    either = u64Value;
    REQUIRE(either.is<u64>());
}
