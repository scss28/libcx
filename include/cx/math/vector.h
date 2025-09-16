#pragma once

#include "cx/nums.h"
#include "cx/math.h"

namespace cx::math {
    template <typename T, usize N>
    struct Vector;

    template <typename T>
    struct Vector<T, 2> {
        T x;
        T y;

        static constexpr Vector<T, 2> splat(T scalar) {
            return {scalar, scalar};
        }

        static constexpr Vector<T, 2> zero() {
            return splat(math::zero<T>());
        }

        static constexpr Vector<T, 2> one() {
            return splat(math::one<T>());
        }

        static constexpr Vector<T, 2> unitX() {
            return {math::one<T>(), math::zero<T>()};
        }

        static constexpr Vector<T, 3> unitY() {
            return {math::zero<T>(), math::one<T>()};
        }

        __forceinline T dot(Vector<T, 2> rhs) const {
            return x * rhs.x + y * rhs.y;
        }

        __forceinline T lenSq() const {
            return dot(*this);
        }

        __forceinline T len() const {
            return sqrt(lenSq());
        }

        T distance(Vector<T, 2> rhs) const {
            T delta = rhs - this;
            return delta.len();
        }

        __forceinline Vector<T, 2> normalize() {
            return this / len();
        }

        Vector<T, 2> normalize(Vector<T, 2> fallback) {
            T length = len();
            if (length == 0) return fallback;

            return this / length;
        }

        __forceinline Vector<T, 2> direction(Vector<T, 2> rhs) const {
            return (rhs - this).normalize();
        }

        Vector<T, 2> direction(Vector<T, 2> rhs, Vector<T, 2> fallback) const {
            T length = len();
            if (length == 0) return fallback;

            return (rhs - this) / length;
        }

        __forceinline Vector<T, 2> operator+(Vector<T, 2> rhs) const {
            return {x + rhs.x, y + rhs.y};
        }
        
        __forceinline Vector<T, 2> operator-(Vector<T, 2> rhs) const {
            return {x - rhs.x, y - rhs.y};
        }
        
        __forceinline Vector<T, 2> operator*(Vector<T, 2> rhs) const {
            return {x * rhs.x, y * rhs.y};
        }

        __forceinline Vector<T, 2> operator/(Vector<T, 2> rhs) const {
            return {x / rhs.x, y / rhs.y};
        }

        __forceinline Vector<T, 2> operator*(T scalar) const {
            return {x * scalar, y * scalar};
        }

        friend __forceinline Vector<T, 2> operator*(T scalar, Vector<T, 2> vec) {
            return {vec.x * scalar, vec.y * scalar};
        }

        __forceinline Vector<T, 2> operator/(T scalar) const {
            return {x / scalar, y / scalar};
        }

        __forceinline Vector<T, 2> operator-() const {
            return {-x, -y};
        }
    };

    template <typename T>
    struct Vector<T, 3> {
        T x;
        T y;
        T z;

        static constexpr Vector<T, 3> splat(T scalar) {
            return {scalar, scalar, scalar};
        }

        static constexpr Vector<T, 3> zero() {
            return splat(math::zero<T>());
        }

        static constexpr Vector<T, 3> one() {
            return splat(math::one<T>());
        }

        static constexpr Vector<T, 3> unitX() {
            return {math::one<T>(), math::zero<T>(), math::zero<T>()};
        }

        static constexpr Vector<T, 3> unitY() {
            return {math::zero<T>(), math::one<T>(), math::zero<T>()};
        }

        static constexpr Vector<T, 3> unitZ() {
            return {math::zero<T>(), math::zero<T>(), math::one<T>()};
        }

         __forceinline T dot(Vector<T, 3> rhs) const {
            return x * rhs.x + y * rhs.y + z * rhs.z;
        }

        __forceinline T lenSq() const {
            return dot(*this);
        }

        __forceinline T len() const {
            return sqrt(lenSq());
        }

        __forceinline T distance(Vector<T, 3> rhs) const {
            T delta = rhs - this;
            return delta.len();
        }

        __forceinline Vector<T, 3> normalize() const {
            return this / len();
        }

        __forceinline Vector<T, 3> normalize(Vector<T, 3> fallback) const {
            T length = len();
            if (length == 0) return fallback;
            return this / length;
        }

        __forceinline Vector<T, 3> direction(Vector<T, 3> rhs) const {
            return (rhs - this).normalize();
        }

        __forceinline Vector<T, 3> direction(Vector<T, 3> rhs, Vector<T, 3> fallback) const {
            T length = (rhs - this).len();
            if (length == 0) return fallback;
            return (rhs - this) / length;
        }

        __forceinline Vector<T, 3> operator+(Vector<T, 3> rhs) const {
            return {x + rhs.x, y + rhs.y, z + rhs.z};
        }

        __forceinline Vector<T, 3> operator-(Vector<T, 3> rhs) const {
            return {x - rhs.x, y - rhs.y, z - rhs.z};
        }

        __forceinline Vector<T, 3> operator*(Vector<T, 3> rhs) const {
            return {x * rhs.x, y * rhs.y, z * rhs.z};
        }

        __forceinline Vector<T, 3> operator/(Vector<T, 3> rhs) const {
            return {x / rhs.x, y / rhs.y, z / rhs.z};
        }

        __forceinline Vector<T, 3> operator*(T scalar) const {
            return {x * scalar, y * scalar, z * scalar};
        }

        friend __forceinline Vector<T, 3> operator*(T scalar, Vector<T, 3> vec) {
            return {vec.x * scalar, vec.y * scalar, vec.z * scalar};
        }

        __forceinline Vector<T, 3> operator/(T scalar) const {
            return {x / scalar, y / scalar, z / scalar};
        }

        __forceinline Vector<T, 3> operator-() const {
            return {-x, -y, -z};
        }
    };

    template <typename T>
    struct Vector<T, 4> {
        T x;
        T y;
        T z;
        T w;

        static constexpr Vector<T, 4> splat(T scalar) {
            return {scalar, scalar, scalar, scalar};
        }

        static constexpr Vector<T, 4> zero() {
            return splat(math::zero<T>());
        }

        static constexpr Vector<T, 4> one() {
            return splat(math::one<T>());
        }

        static constexpr Vector<T, 4> unitX() {
            return {math::one<T>(), math::zero<T>(), math::zero<T>(), math::zero<T>()};
        }

        static constexpr Vector<T, 4> unitY() {
            return {math::zero<T>(), math::one<T>(), math::zero<T>(), math::zero<T>()};
        }

        static constexpr Vector<T, 4> unitZ() {
            return {math::zero<T>(), math::zero<T>(), math::one<T>(), math::zero<T>()};
        }

        static constexpr Vector<T, 4> unitW() {
            return {math::zero<T>(), math::zero<T>(), math::zero<T>(), math::one<T>()};
        }

        __forceinline T dot(Vector<T, 4> rhs) const {
            return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
        }

        __forceinline T lenSq() const {
            return dot(this);
        }

        __forceinline T len() const {
            return sqrt(lenSq());
        }

        __forceinline T distance(Vector<T, 4> rhs) const {
            auto delta = rhs - this;
            return delta.len();
        }

        __forceinline Vector<T, 4> normalize() const {
            return this / len();
        }

        __forceinline Vector<T, 4> normalize(Vector<T, 4> fallback) const {
            T length = len();
            if (length == 0) return fallback;
            return this / length;
        }

        __forceinline Vector<T, 4> direction(Vector<T, 4> rhs) const {
            return (rhs - this).normalize();
        }

        __forceinline Vector<T, 4> direction(Vector<T, 4> rhs, Vector<T, 4> fallback) const {
            T length = (rhs - this).len();
            if (length == 0) return fallback;
            return (rhs - this) / length;
        }

        __forceinline Vector<T, 4> operator+(Vector<T, 4> rhs) const {
            return {x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w};
        }

        __forceinline Vector<T, 4> operator-(Vector<T, 4> rhs) const {
            return {x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w};
        }

        __forceinline Vector<T, 4> operator*(Vector<T, 4> rhs) const {
            return {x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w};
        }

        __forceinline Vector<T, 4> operator/(Vector<T, 4> rhs) const {
            return {x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w};
        }

        __forceinline Vector<T, 4> operator*(T scalar) const {
            return {x * scalar, y * scalar, z * scalar, w * scalar};
        }

        friend __forceinline Vector<T, 4> operator*(T scalar, Vector<T, 4> vec) {
            return {vec.x * scalar, vec.y * scalar, vec.z * scalar, vec.w * scalar};
        }

        __forceinline Vector<T, 4> operator/(T scalar) const {
            return {x / scalar, y / scalar, z / scalar, w / scalar};
        }

        __forceinline Vector<T, 4> operator-() const {
            return {-x, -y, -z, -w};
        }
    };

    using Vector2 = Vector<f32, 2>;
    using Vector3 = Vector<f32, 3>;
    using Vector4 = Vector<f32, 4>;
}
