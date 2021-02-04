#pragma once
#include "InputDevice.hpp"
#include "Common/Type/MapWrapper.hpp"
#include "InputState.hpp"

namespace Nano
{
    class InputDeviceKeyboard : InputDevice
    {
    public:
        void Update(float dt) final {};
        bool GetBoolKeyDown(Key key) override;

    private:
        HashMap<Key, InputState> m_KeyInputStateMap;
    };
}