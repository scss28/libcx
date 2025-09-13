#pragma once

#include "cx/io/file.h"

namespace cx::io {
    struct Dir {
        typedef struct Handle* Handle;
        Handle handle;

        Either<File, File::OpenError> openFile(Slice<const u8> path);
    };
}
