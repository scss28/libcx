#pragma once
#include "cx/nums.h"

namespace cx::time {
    struct Instant {
        u64 timestamp;
        u64 nsSince(Instant other);
    };
}
