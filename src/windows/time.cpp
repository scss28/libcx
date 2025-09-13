#include "cx/mem.h"
#include "cx/time.h"

#include <profileapi.h>

namespace cx::time {
    Instant Instant::now() {
        LARGE_INTEGER count;
        QueryPerformanceCounter(&count);

        return { .timestamp = mem::bitCast<u64>(count) };
    }

    u64 clockFrequency() {
        LARGE_INTEGER frequency;
        QueryPerformanceFrequency(&frequency);

        return mem::bitCast<u64>(frequency);
    }

    u64 between(Instant start, Instant end) {
        u64 qpf = clockFrequency();
        u64 qpc = end.timestamp - start.timestamp;

        const u64 commonFrequency = 10000000;
        if (qpf == commonFrequency) {
            return qpc * (NS_PER_S / commonFrequency);
        }
        
        u64 scale = (NS_PER_S << 32) / qpf;
        return (qpc * scale) >> 32;
    }
}
