#include <windows.h>

#include "cx/io/file.h"
#include "cx/mem.h"

namespace cx::io {
    void File::close() const {
        CloseHandle(mem::bitCast<HANDLE>(handle));
    }

    Either<usize, File::WriteError> File::write(const Slice<const u8> bytes) const {
        DWORD written;
        WriteFile(mem::bitCast<HANDLE>(handle), bytes.ptr, bytes.len, &written, nullptr);

        return written;
    }
}
