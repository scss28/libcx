#include "cx/math.h"
#include "cx/arr.h"
#include "cx/mem.h"

namespace cx::math {
    template <typename T, usize W, usize H, bool RowMajor = true>
    struct Matrix {
        T data[W * H];

        using Self = Matrix<T, W, H, RowMajor>;

        constexpr Self splat(T scalar) {
            Self matrix;

            mem::set(matrix.data, scalar);
            return matrix;
        }
    };
}
