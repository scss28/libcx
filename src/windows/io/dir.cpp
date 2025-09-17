#include "cx/io/dir.h"
#include "cx/program.h"

namespace cx::io {
    Either<File, File::OpenError> Dir::openFile(Slice<const u8> path) {
        (void)path;
        panic();
    }
}
