#pragma once

#include "InputDevice.hpp"

namespace Nano
{
    class InputDeviceMouse : public InputDevice
    {
        void Update(float dt) override;

        InputDeviceType inline GetDeviceType() const { return InputDeviceType::_Mouse; }

        bool GetBoolKeyDown(InputKey key) override;

        bool GetBoolKeyRelease(InputKey key) override;

        bool GetBoolKeyClick(InputKey key) override;

        bool GetBoolKeyPress(InputKey key, float holdTime) override;
    };
}