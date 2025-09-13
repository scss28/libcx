#include "cx/io.h"
#include "cx/mem.h"

namespace cx::io {
    File stdin() {
        return { .handle = (File::Handle)0 };
    }

    File stdout() {
        return { .handle = (File::Handle)1 };
    }

    File stderr() {
        return { .handle = (File::Handle)2 };
    }

    Either<File, File::OpenError> Dir::openFile(Slice<const u8> path) {
        (void)path;
        panic();
    }
}
