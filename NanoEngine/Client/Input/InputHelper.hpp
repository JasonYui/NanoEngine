#pragma once
#include "Common/Fwd.hpp"
#include "InputDefine.hpp"
#include "InputEnum.hpp"

namespace Nano
{
    inline InputDeviceType GetDeviceType(InputKey key)
    {
        return static_cast<InputDeviceType>(static_cast<uint32_t>(key) >> 24);
    }

    inline InputDeviceType GetDeviceType(DeviceID id)
    {
        return static_cast<InputDeviceType>(id >> 24);
    }
}