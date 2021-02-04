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

    void InputManager::DeleteDevice(DeviceID id)
    {
        m_DeviceMap.erase(id);
    }

    bool InputManager::GetBoolKeyDown(Key key)
    {
        for (auto& iter : m_DeviceMap)
        {
            if (iter.second->GetBoolKeyDown(key))
                return true;
        }
        return false;
    }

    bool InputManager::GetBoolKeyRelease(Key key)
    {
        for (auto& iter : m_DeviceMap)
        {
            if (iter.second->GetBoolKeyRelease(key))
                return true;
        }
        return false;
    }
}