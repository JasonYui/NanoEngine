#pragma once
#include "Client/Input/InputDeviceMouse.hpp"

namespace Nano
{
    class InputDeviceMouseWin : public InputDeviceMouse
    {
    public:
        InputDeviceMouseWin();

        void HandleMessage(const MSG& msg);
    };
}