#include "cx/program.h"
#include "cx/io.h"

#ifdef _WIN32
#include "windows/program.cpp"
#else
#include "linux/program.cpp"
#endif

namespace cx {
    [[noreturn]] void panic() {
#if defined(_MSC_VER) && !defined(__clang__) // MSVC
        __debugbreak();
#else // GCC, Clang
        __builtin_unreachable();
#endif
    }

    [[noreturn]] void panic(Slice<u8> msg) {
        (void)io::stderr().writeAll(msg);
        panic();
    }

    [[noreturn]] void unreachable() {
#if defined(_MSC_VER) && !defined(__clang__) // MSVC
        __assume(false);
#else // GCC, Clang
        __builtin_unreachable();
#endif
    }
}
