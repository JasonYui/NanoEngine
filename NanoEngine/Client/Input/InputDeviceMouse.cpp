#include "InputDeviceMouse.hpp"
#include "InputHelper.hpp"

namespace Nano
{
    bool InputDeviceMouse::GetAxisKey(InputKey key, OUT Vector2f& axis)
    {
        return InputHelper::GetAxisKey(m_AxisInputStateMap, key, OUT axis);
    }

    bool InputDeviceMouse::GetBoolKeyDown(InputKey key)
    {
        return InputHelper::GetBoolKeyDown(m_KeyInputStateMap, key);
    }

    bool InputDeviceMouse::GetBoolKeyRelease(InputKey key)
    {
        return InputHelper::GetBoolKeyRelease(m_KeyInputStateMap, key);
    }

    bool InputDeviceMouse::GetBoolKeyClick(InputKey key)
    {
        return InputHelper::GetBoolKeyClick(m_KeyInputStateMap, key);
    }

    bool InputDeviceMouse::GetBoolKeyPress(InputKey key, float holdTime)
    {
        return InputHelper::GetBoolKeyPress(m_KeyInputStateMap, key, holdTime);
    }

    void InputDeviceMouse::HandleButton(InputKey key, bool keyDown)
    {
        InputHelper::HandleButton(m_KeyInputStateMap, key, keyDown);
    }

    void InputDeviceMouse::HandleAxis(InputKey key, Vector2f axis)
    {
        InputHelper::HandleAxis(m_AxisInputStateMap, key, axis);
    }
}