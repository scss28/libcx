#pragma once

#include "cx/io/file.h"
#include "cx/io/dir.h"

namespace cx::io {
    /// Returns the current working directory.
    Dir cwd();

    /// Returns the standard input file.
    File stdin();

    /// Returns the standard output file.
    File stdout();

    /// Returns the standard error file.
    File stderr();
}
