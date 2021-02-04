#pragma once
#include "Common/Fwd.hpp"
#include "InputDefine.hpp"
#include "InputEnum.hpp"

namespace Nano
{
    inline void HandleButton(InputDevice& device, InputState& state, InputDeltaState* delta, DeviceButtonId buttonId, bool value)
    {
#ifdef ENGINE_DEBUG
        if (value != state.GetBool(buttonId))
        {
            LOG_INFO("button changed: %d, %i\n", buttonId, value);
        }
#endif
        if (delta)
        {
            const bool oldValue = state.GetBool(buttonId);
            if (value != oldValue)
            {
                delta->AddChange(device.GetDeviceId(), buttonId, oldValue, value);
            }
        }

        state.Set(buttonId, value);
    }

    inline InputDeviceType GetDeviceType(Key key)
    {
        return static_cast<InputDeviceType>(static_cast<uint32_t>(key) >> 26);
    }
}