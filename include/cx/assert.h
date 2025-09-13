#pragma once

#include "cx/program.h"

#if defined(NDEBUG) || defined(_DEBUG)
#define ASSERT(expression) !(expression) ? cx::unreachable() : ((void)0)
#else
#define ASSERT(expression) ((void)0)
#endif
