#include "gtest/gtest.h"
#include "Client/Input/InputManager.hpp"
#include "Client/Platform/Input/Keyboard/InputDeviceKeyboardWin.hpp"

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