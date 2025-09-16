#pragma once


#include "cx/slice.h"
#include "cx/either.h"
#include "cx/maybe.h"

namespace cx::io {
    struct File {
        enum class OpenError {

        };

        enum class WriteError {

        };

        typedef struct Handle* Handle;
        Handle handle;

        void close() const;

        /// Writes `bytes` to the file. May not write everything, returns the count written.
        Either<usize, WriteError> write(const Slice<const u8> bytes) const;

        /// Same as `write`, but keeps writing until it writes everything.
        Maybe<WriteError> writeAll(const Slice<const u8> bytes) const;
    };
}
