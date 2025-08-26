#include <std/mem.h>

TEST_CASE("isValidAlignment checks alignment properly", "[mem]") {
    REQUIRE(std::isValidAlignment(2) == true);
    REQUIRE(std::isValidAlignment(3) == false);
    REQUIRE(std::isValidAlignment(0) == false);
    REQUIRE(std::isValidAlignment(512) == true);
}
