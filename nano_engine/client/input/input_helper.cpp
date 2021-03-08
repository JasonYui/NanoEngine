#include "client/input/input_helper.hpp"

namespace InputHelper
{
    void HandleButton(HashMap<InputKey, InputState>& keyInputStateMap, InputKey key, bool keyDown)
    {
        auto&& iter = keyInputStateMap.find(key);
        if (iter != keyInputStateMap.end())
        {
            iter->second.prevInputType = iter->second.inputType;
            iter->second.inputType = keyDown ? RawInputType::_Down : RawInputType::_Release;
        }
        else
        {
            InputState state = {};
            state.inputType = keyDown ? RawInputType::_Down : RawInputType::_Release;
            keyInputStateMap.emplace(key, state);
        }
    }

    void HandleAxis(HashMap<InputKey, Vector2f>& axisInputStateMap, InputKey key, Vector2f axis)
    {
        auto&& iter = axisInputStateMap.find(key);
        if (iter != axisInputStateMap.end())
        {
            iter->second = axis;
        }
        else
        {
            axisInputStateMap.emplace(key, axis);
        }
    }

    bool GetBoolKeyDown(const HashMap<InputKey, InputState>& keyInputStateMap, InputKey key)
    {
        auto&& iter = keyInputStateMap.find(key);
        if (iter != keyInputStateMap.end())
        {
            return iter->second.inputType == RawInputType::_Down;
        }
        return false;
    }

    bool GetBoolKeyRelease(const HashMap<InputKey, InputState>& keyInputStateMap, InputKey key)
    {
        auto&& iter = keyInputStateMap.find(key);
        if (iter != keyInputStateMap.end())
        {
            return iter->second.inputType == RawInputType::_Release;
        }
        return false;
    }

    bool GetBoolKeyClick(const HashMap<InputKey, InputState>& keyInputStateMap, InputKey key)
    {
        auto&& iter = keyInputStateMap.find(key);
        if (iter != keyInputStateMap.end())
        {
            return iter->second.inputType == RawInputType::_Down && iter->second.prevInputType == RawInputType::_Down;
        }
        return false;
    }

    bool GetBoolKeyPress(const HashMap<InputKey, InputState>& keyInputStateMap, InputKey key, float holdTime)
    {
        auto&& iter = keyInputStateMap.find(key);
        if (iter != keyInputStateMap.end())
        {
            return iter->second.inputType == RawInputType::_Down && iter->second.holdTime >= holdTime;
        }
        return false;
    }

    bool GetAxisKey(HashMap<InputKey, Vector2f>& axisInputStateMap, InputKey key, OUT Vector2f& axis)
    {
        if (axisInputStateMap.count(key))
        {
            axis = axisInputStateMap[key];
            return true;
        }
        return false;
    }
}