#include "gtest/gtest.h"
#include "client/input/input_manager.hpp"
#include "client/platform/input/keyboard/input_device_keyboard_win.hpp"

using namespace Nano;

namespace Test
{
    TEST(InputTest, Test_DeviceCreate)
    {
        InputManager* inputMgr = new InputManager();
        inputMgr->CreateDevice<InputDeviceKeyboardWin>();
        delete inputMgr;
    }
}