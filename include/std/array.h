#pragma once
#include "std/nums.h"
#include "std/mem.h"

#include <assert.h>

namespace std {
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

        Buf<T> buf() {
            return {data, N};
        }

        constexpr usize len() {
            return N;
        }

        inline T const& operator[](usize index) const {
            assert(index < N);
            return data[index];
        }

        inline Buf<T> operator[](usize start, usize end) const {
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
