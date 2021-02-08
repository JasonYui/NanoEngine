#pragma once

#include "InputDevice.hpp"
#include "Common/Type/MapWrapper.hpp"
#include "InputState.hpp"

namespace Nano
{
    class InputDeviceKeyboard : public InputDevice
    {
    public:
        void Update(float dt) final;

        InputDeviceType inline GetDeviceType() const final { return InputDeviceType::_Keyboard; };

        bool GetBoolKeyDown(InputKey key) final;

        bool GetBoolKeyRelease(InputKey key) final;

        bool GetBoolKeyClick(InputKey key) final;

        bool GetBoolKeyPress(InputKey key, float holdTime) final;

        bool GetAxisKey(InputKey key, OUT Vector2f& axis) final { return false; }

    protected:
        void HandleButton(InputKey key, bool keyDown);

        HashMap<InputKey, InputState> m_KeyInputStateMap;
    };
}