#include <windows.h>
#include <dbghelp.h>
#include <processthreadsapi.h>

#include "cx/program.h"

namespace cx {
    [[noreturn]] void exit(u32 code) {
        ExitProcess(code);
    } 
}
