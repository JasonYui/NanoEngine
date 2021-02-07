#include "InputManager.hpp"
#include "InputDefine.hpp"
#include "InputEnum.hpp"

namespace Nano
{
    void InputManager::Update(float dt)
    {
        for (auto& iter : m_DeviceMap)
        {
            iter.second->Update(dt);
        }
    }

    const InputDevice* InputManager::GetDevice(DeviceID id)
    {
        return m_DeviceMap[id];
    }

    void InputManager::DeleteDevice(DeviceID id)
    {
        m_DeviceMap.erase(id);
    }

    bool InputManager::GetBoolKeyDown(InputKey key)
    {
        for (auto& iter : m_DeviceMap)
        {
            if (iter.second->GetBoolKeyDown(key))
                return true;
        }
        return false;
    }

    bool InputManager::GetBoolKeyRelease(InputKey key)
    {
        for (auto& iter : m_DeviceMap)
        {
            if (iter.second->GetBoolKeyRelease(key))
                return true;
        }
        return false;
    }
}