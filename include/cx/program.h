#pragma once

#include "cx/nums.h"
#include "cx/slice.h"

namespace cx {
    template <typename T>
    struct Slice;

    /// Exits the program with the specified error code.
    [[noreturn]] void exit(u32 code);

    /// Prints the message and exits abnormally (usually prints a stack trace).
    [[noreturn]] void panic(Slice<u8> msg);

    /// Causes the program to exit abnormally (usually prints a stack trace).
    [[noreturn]] void panic();

    /// In debug mode, this will panic.
    /// Otherwise triggers undefined behaviour.
    [[noreturn]] void unreachable();
}
