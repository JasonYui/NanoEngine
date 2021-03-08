#pragma once
#include <windows.h>
#include <winuser.h>

#include "client/input/input_device_mouse.hpp"

namespace Nano
{
    class InputDeviceMouseWin : public InputDeviceMouse
    {
    public:
        InputDeviceMouseWin();

        void HandleMessage(const MSG& msg);
    };
}