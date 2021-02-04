#include "InputManager.hpp"
#include "InputDefine.hpp"

namespace Nano
{
    void InputManager::Update(float dt)
    {
        for (auto& iter : m_DeviceMap)
        {
            iter.second->Update(dt);
        }
    }

    template<typename T>
    DeviceID InputManager::CreateDevice()
    {
        DeviceID id = m_NextDeviceID;
        T* device = new T();
	    m_DeviceMap[id] = device;
        m_NextDeviceID++;
        return id;
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
}