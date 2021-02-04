#include "InputDeviceKeyboard.hpp"
#include "InputEnum.hpp"

namespace Nano
{
    bool InputDeviceKeyboard::GetBoolKeyDown(Key key)
    {
        auto iter = m_KeyInputStateMap.find(key);
        if (iter != m_KeyInputStateMap.end())
        {
            return iter->second.m_InputType == BaseInputType::_Down;
        }
        return false;
    }
}