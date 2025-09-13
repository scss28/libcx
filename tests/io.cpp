// Something has macros defined for these for some reason...
#undef stdout
#undef stdin
#undef stderr

#include <cx/io.h>

namespace io = cx::io;

TEST_CASE("Printing to stdout", "[io]") {
    REQUIRE(!io::stdout().writeAll("hello\n").hasValue());
}
