#include "cx/io/file.h"

namespace cx::io {
    Maybe<File::WriteError> File::writeAll(const Slice<const u8> bytes) const {
        auto slice = bytes;
        while (slice.len > 0) {
            auto result = write(slice);
            if (result.is<File::WriteError>()) return result.unwrap<File::WriteError>();

            slice.len -= result.unwrap<usize>();
        }

        return nullptr;
    }
}
