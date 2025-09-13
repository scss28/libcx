#include "cx/nums.h"

namespace cx {
    /// Exits the program with the specified error code.
    [[noreturn]] void exit(i32 code);

    /// Writes the stack trace to stderr and exits the program.
    [[noreturn]] void panic();

    /// In debug mode, this will panic.
    /// Otherwise triggers undefined behaviour.
    [[noreturn]] void unreachable();
}
