#pragma once

#include "common/math/vector.hpp"
#include "common/type/map_wrapper.hpp"

#include "client/input/input_device.hpp"


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