#include "InputDeviceKeyboard.hpp"
#include "InputEnum.hpp"

namespace Nano
{
    void InputDeviceKeyboard::Update(float dt)
    {
        for (auto& iter : m_KeyInputStateMap)
        {
            if (iter.second.prevInputType == BaseInputType::_Down && iter.second.inputType == BaseInputType::_Down)
            {
                iter.second.holdTime += dt;
            }
        }
    }

    bool InputDeviceKeyboard::GetBoolKeyDown(InputKey key)
    {
        auto iter = m_KeyInputStateMap.find(key);
        if (iter != m_KeyInputStateMap.end())
        {
            return iter->second.inputType == BaseInputType::_Down;
        }
        return false;
    }
    
    bool InputDeviceKeyboard::GetBoolKeyRelease(InputKey key)
    {
        auto iter = m_KeyInputStateMap.find(key);
        if (iter != m_KeyInputStateMap.end())
        {
            return iter->second.inputType == BaseInputType::_Release;
        }
        return false;
    }

    bool InputDeviceKeyboard::GetBoolKeyClick(InputKey key)
    {
        auto iter = m_KeyInputStateMap.find(key);
        if (iter != m_KeyInputStateMap.end())
        {
            return iter->second.inputType == BaseInputType::_Down && iter->second.prevInputType == BaseInputType::_Down;
        }
        return false;
    }

    bool InputDeviceKeyboard::GetBoolKeyPress(InputKey key, float holdTime)
    {
        auto iter = m_KeyInputStateMap.find(key);
        if (iter != m_KeyInputStateMap.end())
        {
            return iter->second.inputType == BaseInputType::_Down && iter->second.holdTime >= holdTime;
        }
        return false;
    }

    void InputDeviceKeyboard::HandleButton(InputKey key, bool keyDown)
    {
        auto iter = m_KeyInputStateMap.find(key);
        if (iter != m_KeyInputStateMap.end())
        {
            iter->second.prevInputType = iter->second.inputType;
            iter->second.inputType = keyDown ? BaseInputType::_Down : BaseInputType::_Release;
        }
    }
}