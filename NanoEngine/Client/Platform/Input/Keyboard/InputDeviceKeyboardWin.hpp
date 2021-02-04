#pragma once

#include "Common/Type/MapWrapper.hpp"
#include "Client/Input/InputDeviceKeyboard.hpp"
#include "Client/Input/InputDefine.hpp"
#include "Client/Input/InputEnum.hpp"
#include <winuser.h>

namespace Nano
{
    HashMap<uint32_t, Key> g_KeyMapping = {
            {VK_ESCAPE, Key::_KeyEscape},
            {VK_F1, Key::_KeyF1}
    };

    class InputDeviceKeyboardWin : public InputDeviceKeyboard
    {
    public:
        void HandleMessage(const MSG& msg);


    private:
    };
}