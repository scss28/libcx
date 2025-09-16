#pragma once

#include "cx/assert.h"

namespace cx {
    template <typename T>
    struct Maybe {
        Maybe(T value) : _hasValue(true), _value(value) {}
        Maybe(decltype(nullptr)) : _hasValue(false) {}

        T unwrap() const {
            ASSERT(this != nullptr);
            return _value;
        }

        bool operator==(decltype(nullptr)) const {
            return !_hasValue;
        }

    private:
        bool _hasValue;
        T _value;
    };

    template <typename T>
    struct Maybe<T*> {
        Maybe(T* value) : _value(value) {}
        Maybe(decltype(nullptr)) : _value(nullptr) {}

        T* unwrap() const {
            ASSERT(this != nullptr);
            return _value;
        }

        bool operator==(decltype(nullptr)) const {
            return _value == nullptr;
        }

    private:
        T* _value;
    };

    template <typename T>
    bool operator==(decltype(nullptr), Maybe<T> maybe) {
        return maybe == nullptr;
    }
}
