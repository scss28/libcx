#include "cx/nums.h"
#include "cx/time.h"
#include "cx/math.h"

#include <windows.h>

namespace cx::thread {
    void sleep(u64 ns) {
        Sleep(static_cast<DWORD>(ns / time::nsPerMs));
    }
}
