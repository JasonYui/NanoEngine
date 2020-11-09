#pragma once
#include "PixelEngine/Common/Type/BasicType.hpp"

namespace Pixel
{
    enum class TaskPriority : uint8_t
    {
        _HIGH,
        _ABOVE_NORMAL,
        _NORMAL,
        _BELOW_NORMAL,
        _LOW,
        _SIZE = 5
    };
}