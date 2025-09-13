#include <windows.h>

#include "cx/io.h"
#include "cx/windows.h"
#include "cx/mem.h"

namespace cx::io {
    File stdin() {
        return { .handle = (File::Handle)windows::peb()->ProcessParameters->hStdInput };
    }
    
    File stdout() {
        return { .handle = (File::Handle)windows::peb()->ProcessParameters->hStdOutput };
    }

    File stderr() {
        return { .handle = (File::Handle)windows::peb()->ProcessParameters->hStdError };
    }

    Either<File, File::OpenError> Dir::openFile(Slice<const u8> path) {
        (void)path;
        panic();
    }
}
