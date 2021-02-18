#pragma once
#include <windows.h>
#include <winuser.h>

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