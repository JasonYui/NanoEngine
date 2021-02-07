#pragma once

#include <windows.h>
#include <winuser.h>

#include "Common/Type/MapWrapper.hpp"

#include "Client/Input/InputDeviceKeyboard.hpp"
#include "Client/Input/InputDefine.hpp"
#include "Client/Input/InputEnum.hpp"

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