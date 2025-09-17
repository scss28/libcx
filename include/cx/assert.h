#pragma once

#if defined(_DEBUG) || defined(NDEBUG)
#include "cx/program.h"
#define ASSERT(expression) !(expression) ? cx::unreachable() : ((void)0)
#else
#define ASSERT(expression) ((void)0)
#endif
