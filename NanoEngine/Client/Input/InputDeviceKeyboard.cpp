#include "InputDeviceKeyboard.hpp"
#include "InputEnum.hpp"
#include "InputHelper.hpp"

namespace Nano
{
    void InputDeviceKeyboard::Update(float dt)
    {
        for (auto& iter : m_KeyInputStateMap)
        {
            if (iter.second.prevInputType == RawInputType::_Down && iter.second.inputType == RawInputType::_Down)
            {
                iter.second.holdTime += dt;
            }
        }
    }

    bool InputDeviceKeyboard::GetBoolKeyDown(InputKey key)
    {
        return InputHelper::GetBoolKeyDown(m_KeyInputStateMap, key);
    }
    
    bool InputDeviceKeyboard::GetBoolKeyRelease(InputKey key)
    {
        return InputHelper::GetBoolKeyRelease(m_KeyInputStateMap, key);
    }

    bool InputDeviceKeyboard::GetBoolKeyClick(InputKey key)
    {
        return InputHelper::GetBoolKeyClick(m_KeyInputStateMap, key);
    }

    bool InputDeviceKeyboard::GetBoolKeyPress(InputKey key, float holdTime)
    {
        return InputHelper::GetBoolKeyPress(m_KeyInputStateMap, key, holdTime);
    }

    void InputDeviceKeyboard::HandleButton(InputKey key, bool keyDown)
    {
        InputHelper::HandleButton(m_KeyInputStateMap, key, keyDown);
    }
}