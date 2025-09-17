#include <cx/mem.h>

namespace mem = cx::mem;

TEST_CASE("isValidAlignment checks alignment properly", "[mem]") {
    ASSERT(false);

    REQUIRE(mem::isValidAlignment(2) == true);
    REQUIRE(mem::isValidAlignment(3) == false);
    REQUIRE(mem::isValidAlignment(0) == false);
    REQUIRE(mem::isValidAlignment(512) == true);
}
