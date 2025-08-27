#include <cx/time.h>
#include <cx/thread.h>

namespace thread = cx::thread;

TEST_CASE("Instant correctly calculates time since", "[time]") {
    const u64 sleepTime = cx::time::nsPerMs * 10;

    auto start = cx::time::now();
    thread::sleep(sleepTime);

    auto elapsed = cx::time::between(start, cx::time::now());
    REQUIRE_THAT(elapsed, Catch::Matchers::WithinAbs(sleepTime, cx::time::nsPerMs));
}
