#include "cx/program.h"
#include <stdlib.h> // @libc

#ifdef _WIN32
#include "windows/program.cpp"
#else
#include "linux/program.cpp"
#endif

namespace cx {
    [[noreturn]] void exit(i32 code) {
        ::exit(code);
    }

    [[noreturn]] void panic() {
        // printStackTrace();
        exit(1);
    }

    [[noreturn]] void unreachable() {
#if defined(_DEBUG) || defined(NDEBUG)
        panic();
#else
#if defined(_MSC_VER) && !defined(__clang__) // MSVC
        __assume(false);
#else // GCC, Clang
        __builtin_unreachable();
#endif
#endif 
    }
}
