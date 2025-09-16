#pragma once

#include "cx/nums.h"
#include "cx/slice.h"

namespace cx::arr {
    template <typename T, usize N>
    __forceinline usize len(T arr[N]) {
        (void)arr;
        return N;
    }

    template <typename T, usize N>
    Slice<T> toSlice(T arr[N]) {
        return {arr, N};
    }
}
