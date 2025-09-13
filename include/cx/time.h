#pragma once
#include "cx/nums.h"

namespace cx::time {
    struct Instant {
        u64 timestamp;

        static Instant now();
    };

    u64 between(Instant start, Instant end);

    inline const u64 NS_PER_US = 1000;
    inline const u64 NS_PER_MS = 1000 * NS_PER_US;
    inline const u64 NS_PER_S = 1000 * NS_PER_MS;
    inline const u64 NS_PER_MIN = 60 * NS_PER_S;
    inline const u64 NS_PER_H = 60 * NS_PER_MIN;
    inline const u64 NS_PER_DAY = 24 * NS_PER_H;
    
    inline const u64 US_PER_MS = 1000;
    inline const u64 US_PER_S = 1000 * US_PER_MS;
    inline const u64 US_PER_MIN = 60 * US_PER_S;
    inline const u64 US_PER_H = 60 * US_PER_MIN;
    inline const u64 US_PER_DAY = 24 * US_PER_H;
    
    inline const u64 MS_PER_S = 1000;
    inline const u64 MS_PER_MIN = 60 * MS_PER_S;
    inline const u64 MS_PER_H = 60 * MS_PER_MIN;
    inline const u64 MS_PER_DAY = 24 * MS_PER_H;
    
    inline const u64 S_PER_MIN = 60;
    inline const u64 S_PER_H = 60 * S_PER_MIN;
    inline const u64 S_PER_DAY = 24 * S_PER_H;
}

