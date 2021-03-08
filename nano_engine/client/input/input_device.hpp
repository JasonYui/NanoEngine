#pragma once
#include "client/input/input_state.hpp"
#include "client/input/input_enum.hpp"

namespace Nano
{
    class InputDevice
    {
    public:
        virtual void Update(float dt) = 0;

        virtual InputDeviceType inline GetDeviceType() const = 0;

        virtual bool GetBoolKeyDown(InputKey key) = 0;

        virtual bool GetBoolKeyRelease(InputKey key) = 0;

        virtual bool GetBoolKeyClick(InputKey key) = 0;

        virtual bool GetBoolKeyPress(InputKey key, float holdTime) = 0;

        virtual bool GetAxisKey(InputKey key, OUT Vector2f& axis) = 0;
    };
}