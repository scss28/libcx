#include <windows.h>

#include "cx/io.h"
#include "cx/windows.h"
#include "cx/mem.h"

namespace cx::io {
    File stdin() {
        auto handle = 
            mem::bitCast<File::Handle>(windows::peb()->ProcessParameters->hStdInput);

        return { .handle = handle };
    }
    
    File stdout() {
        auto handle = 
            mem::bitCast<File::Handle>(windows::peb()->ProcessParameters->hStdOutput);
        return { .handle = handle };
    }

    File stderr() {
        auto handle = 
            mem::bitCast<File::Handle>(windows::peb()->ProcessParameters->hStdError);
        return { .handle = handle };
    }
}
