#pragma once

#include <windows.h>
#include <winuser.h>

#include "common/type/map_wrapper.hpp"

#include "client/input/input_device_keyboard.hpp"
#include "client/input/input_define.hpp"
#include "client/input/input_enum.hpp"

namespace Nano
{
    class InputDeviceKeyboardWin : public InputDeviceKeyboard
    {
    public:
        InputDeviceKeyboardWin();

        void HandleMessage(const MSG& msg);

    private:
        static const HashMap<uint32_t, InputKey> s_KeyMapping;
    };
}