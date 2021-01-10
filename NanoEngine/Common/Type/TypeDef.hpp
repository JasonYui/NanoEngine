
#pragma once

#include <stdint.h>
#include <stdbool.h>

namespace Nano
{
    #define _interface_ class

    #ifdef _ATTRIBUTE_
    #define ATTRIBUTE(...) __attribute__((annotate(#__VA_ARGS__)))
    #else
    #define ATTRIBUTE(...)
    #endif
}