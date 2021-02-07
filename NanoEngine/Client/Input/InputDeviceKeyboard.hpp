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

        bool GetBoolKeyDown(InputKey key) override;

        bool GetBoolKeyRelease(InputKey key) override;

        bool GetBoolKeyClick(InputKey key) override;

        bool GetBoolKeyPress(InputKey key, float holdTime);

    protected:
        void HandleButton(InputKey key, bool keyDown);

        HashMap<InputKey, InputState> m_KeyInputStateMap;
    };
}