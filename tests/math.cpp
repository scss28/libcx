#include <cx/math.h>

namespace math = cx::math;

TEST_CASE("math::lerp returns correct values", "[math]") {
    REQUIRE(math::lerp(10, 20, 0.5f) == 15);
}
