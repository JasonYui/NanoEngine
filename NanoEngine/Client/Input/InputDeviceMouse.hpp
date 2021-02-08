#pragma once

#include "InputDevice.hpp"

#include "Common/Math/Vector.hpp"
#include "Common/Type/MapWrapper.hpp"

namespace Nano
{
    class InputDeviceMouse : public InputDevice
    {
    public:
        void Update(float dt) override {};

        InputDeviceType inline GetDeviceType() const { return InputDeviceType::_Mouse; }

        bool GetBoolKeyDown(InputKey key) final;

        bool GetBoolKeyRelease(InputKey key) final;

        bool GetBoolKeyClick(InputKey key) final;

        bool GetBoolKeyPress(InputKey key, float holdTime) final;

        bool GetAxisKey(InputKey key, OUT Vector2f& axis) final;

    protected:
        void HandleButton(InputKey key, bool keyDown);
        void HandleAxis(InputKey key, Vector2f axis);

        HashMap<InputKey, InputState> m_KeyInputStateMap;
        HashMap<InputKey, Vector2f> m_AxisInputStateMap;
    };
}