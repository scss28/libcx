#pragma once

#include <stdint.h>

using i8 = signed char;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using u8 = char;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using f32 = float;
using f64 = double;

using isize = intptr_t;
using usize = uintptr_t;

#if defined(__GNUC__) || defined (__clang__)
#define INT128
#endif

#ifdef INT128
using i128 = __int128;
using u128 = unsigned __int128;
#endif
