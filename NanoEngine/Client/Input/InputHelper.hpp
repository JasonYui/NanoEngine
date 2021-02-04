#pragma once
#include "Common/Fwd.hpp"
#include "InputDefine.hpp"
#include "InputEnum.hpp"

namespace Nano
{
    inline InputDeviceType GetDeviceType(Key key)
    {
        return static_cast<InputDeviceType>(static_cast<uint32_t>(key) >> 24);
    }
}