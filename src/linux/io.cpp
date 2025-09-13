#include "cx/io.h"
#include "cx/linux.h"
#include "cx/mem.h"

namespace cx::io {
    File stdin() {
        return { .handle = mem::bitCast<File::Handle>(linux::STDIN_FILENO) };
    }

    File stdout() {
        return { .handle = mem::bitCast<File::Handle>(linux::STDOUT_FILENO) };
    }

    File stderr() {
        return { .handle = mem::bitCast<File::Handle>(linux::STDERR_FILENO) };
    }

    Either<File, File::OpenError> Dir::openFile(Slice<const u8> path) {
        (void)path;
        panic();
    }
}
