#include "gtest/gtest.h"
#include "Client/Input/InputManager.hpp"

using namespace Nano;

namespace Test
{
    TEST(InputTest, Test_DeviceCreate)
    {
        InputManager* inputMgr = new InputManager();
        //inputMgr->CreateDevice<InputDevice>();
        delete inputMgr;
    }
}