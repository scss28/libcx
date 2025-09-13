#pragma once

#include "cx/assert.h"

namespace cx {
    template <typename T>
    struct Maybe {
        Maybe(T value) : _hasValue(true), _value(value) {}
        Maybe(decltype(nullptr)) : _hasValue(false) {}

        inline bool hasValue() {
            return _hasValue;
        }

        T unwrap() const {
            ASSERT(hasValue());
            return _value;
        }

        void assertNull() const {
            ASSERT(!hasValue());
        }

    private:
        bool _hasValue;
        T _value;
    };

    template <typename T>
    struct Maybe<T*> {
        Maybe(T* value) : _value(value) {}
        Maybe(decltype(nullptr)) : _value(nullptr) {}

        inline bool hasValue() {
            return _value != nullptr;
        }

        T* unwrap() const {
            ASSERT(hasValue());
            return _value;
        }

        void assertNull() const {
            ASSERT(!hasValue());
        }

    private:
        T* _value;
    };
}
