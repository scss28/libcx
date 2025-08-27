#pragma once
#include "cx/nums.h"

namespace cx::time {
    struct Instant;
    Instant now();
    u64 between(Instant start, Instant end);

    inline const u64 nsPerUs = 1000;
    inline const u64 nsPerMs = 1000 * nsPerUs;
    inline const u64 nsPerS = 1000 * nsPerMs;
    inline const u64 nsPerMin = 60 * nsPerS;
    inline const u64 nsPerH = 60 * nsPerMin;
    inline const u64 nsPerDay = 24 * nsPerH;
    
    inline const u64 usPerMs = 1000;
    inline const u64 usPerS = 1000 * usPerMs;
    inline const u64 usPerMin = 60 * usPerS;
    inline const u64 usPerH = 60 * usPerMin;
    inline const u64 usPerDay = 24 * usPerH;
    
    inline const u64 msPerS = 1000;
    inline const u64 msPerMin = 60 * msPerS;
    inline const u64 msPerH = 60 * msPerMin;
    inline const u64 msPerDay = 24 * msPerH;
    
    inline const u64 sPerMin = 60;
    inline const u64 sPerH = 60 * sPerMin;
    inline const u64 sPerDay = 24 * sPerH;
}

#ifdef _WIN32
#include "cx/windows/time.h"
#elifdef __linux__ 
#include "cx/linux/time.h"
#endif
