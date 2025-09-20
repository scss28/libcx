#pragma once

#include "cx/nums.h"
#include "cx/slice.h"

namespace cx::arr {
    template <typename T, usize N>
    constexpr usize len(T (&)[N]) {
        return N;
    }

    /// Slices the array from `start` to the array length.
    template <typename T, usize N>
    Slice<T> from(T (&arr)[N], usize start) {
        return Slice(arr).from(start);
    }

    /// Slices the array up to `end`.
    template <typename T, usize N>
    Slice<T> to(T (&arr)[N], usize end) {
        return Slice(arr).to(end);
    }
}
