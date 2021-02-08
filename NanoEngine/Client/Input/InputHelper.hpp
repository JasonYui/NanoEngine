#pragma once
#include "Common/Fwd.hpp"
#include "Common/Type/MapWrapper.hpp"

#include "InputDefine.hpp"
#include "InputEnum.hpp"
#include "InputState.hpp"

using namespace Nano;
namespace InputHelper
{
    inline InputDeviceType GetDeviceType(InputKey key)
    {
        return static_cast<InputDeviceType>(static_cast<uint32_t>(key) >> 24);
    }

    inline InputDeviceType GetDeviceType(DeviceId id)
    {
        return static_cast<InputDeviceType>(id >> 24);
    }

    void HandleButton(HashMap<InputKey, InputState>& keyInputStateMap, InputKey key, bool keyDown);

    void HandleAxis(HashMap<InputKey, Vector2f>& axisInputStateMap, InputKey key, Vector2f axis);

    bool GetBoolKeyDown(const HashMap<InputKey, InputState>& keyInputStateMap, InputKey key);

    bool GetBoolKeyRelease(const HashMap<InputKey, InputState>& keyInputStateMap, InputKey key);

    bool GetBoolKeyClick(const HashMap<InputKey, InputState>& keyInputStateMap, InputKey key);

    bool GetBoolKeyPress(const HashMap<InputKey, InputState>& keyInputStateMap, InputKey key, float holdTime);

    bool GetAxisKey(HashMap<InputKey, Vector2f>& axisInputStateMap, InputKey key, OUT Vector2f& axis);
}