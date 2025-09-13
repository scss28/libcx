#pragma once

#include "cx/nums.h"
#include "cx/assert.h"
#include "cx/maybe.h"

namespace cx {
    template <typename L, typename R>
    struct Either {
        Either(L left) : _tag(Tag::Left), _left(left) {}
        Either(R right) : _tag(Tag::Right), _right(right) {}

        template <typename T>
        bool is() const;

        template <>
        bool is<L>() const {
            return _tag == Tag::Left;
        }

        template <>
        bool is<R>() const {
            return _tag == Tag::Right;
        }
        
        template <typename T>
        T unwrap() const;

        template <>
        L unwrap() const {
            ASSERT(is<L>());
            return _left;
        }

        template <>
        R unwrap() const {
            ASSERT(is<R>());
            return _right;
        }

        template <typename T>
        Maybe<T> get() const;

        template <>
        Maybe<L> get() const {
            return _left;
        }

        template <>
        Maybe<R> get() const {
            return _right;
        }

    private:
        enum Tag : u8 {
            Left,
            Right,
        };

        Tag _tag;
        union {
            L _left;
            R _right;
        };
    };
}
