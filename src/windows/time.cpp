#include "cx/windows/time.h"
#include "cx/mem.h"
#include "cx/time.h"

#include <profileapi.h>

namespace cx::time {
    Instant now() {
        LARGE_INTEGER count;
        QueryPerformanceCounter(&count);

        return { .timestamp = mem::bitCast<u64>(count) };
    }

    u64 between(Instant start, Instant end) {
        LARGE_INTEGER frequency;
        QueryPerformanceFrequency(&frequency);

        u64 qpf = mem::bitCast<u64>(frequency);
        u64 qpc = end.timestamp - start.timestamp;

        const u64 commonFrequency = 10000000;
        if (qpf == commonFrequency) {
            return qpc * (nsPerS / commonFrequency);
        }
        
        u64 scale = (nsPerS << 32) / qpf;
        return (qpc * scale) >> 32;
    }
}
