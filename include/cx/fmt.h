#include "cx/either.h"
#include "cx/slice.h"

namespace cx::fmt {
    struct BufferOverflowError {};

    template <typename T, typename... Args>
    Either<usize, BufferOverflowError> bufPrint(Slice<u8> buf, T arg) {

    }

    template <typename T, typename... Args>
    Either<usize, BufferOverflowError> bufPrint(Slice<u8> buf, T arg, Args... args) {
        // usize len = TRY(bufPrint(buf, arg));
        // bufPrint(buf.from(len), args...);
    }
}
