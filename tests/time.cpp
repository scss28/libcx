#include <cx/time.h>
#include <cx/thread.h>

namespace thread = cx::thread;

TEST_CASE("Instant correctly calculates time since", "[time]") {
    const u64 sleepTime = cx::time::NS_PER_MS * 20;

    auto start = cx::time::Instant::now();
    thread::sleep(sleepTime);

    auto elapsed = cx::time::between(start, cx::time::Instant::now());
    REQUIRE_THAT(elapsed, Catch::Matchers::WithinAbs(sleepTime, 10 * cx::time::NS_PER_MS));
}
