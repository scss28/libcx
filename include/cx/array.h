#pragma once
#include "cx/nums.h"
#include "cx/slice.h"
#include "cx/mem.h"

#include <assert.h>

namespace cx {
    template <typename T, usize N>
    struct Array {
        T data[N];

#ifdef DEBUG
        Array() : data(std::zeros<T[N]>()) {}
#else
        Array() {}
#endif
        Array(T d[N]) {
            for (usize i = 0; i < N; i++) data[i] = d[i];
        }

        constexpr usize len() {
            return N;
        }

        inline T const& operator[](usize index) const {
            assert(index < N);
            return data[index];
        }

        inline Slice<T> operator[](usize start, usize end) const {
            assert(end >= start);
            assert(end <= N);
            return { data + start, end - start };
        }

        T* begin() {
            return data;
        }

        T* end() { 
            return data + N;
        }
    };

    template <typename T, typename... Args>
    Array<T, sizeof...(Args)> arr(Args... args) {
        T data[] = { static_cast<T>(args)... };
        return {data};
    }
}
