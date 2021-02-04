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

        bool GetBoolKeyDown(Key key) override;

        bool GetBoolKeyRelease(Key key) override;

        bool GetBoolKeyClick(Key key) override;

        bool GetBoolKeyPress(Key key, float holdTime);

    protected:
        void HandleButton(Key key, bool keyDown);

        HashMap<Key, InputState> m_KeyInputStateMap;
    };
}