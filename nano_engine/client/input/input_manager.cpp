#include "client/input/input_manager.hpp"
#include "client/input/input_define.hpp"
#include "client/input/input_enum.hpp"

namespace Nano
{
    void InputManager::Close()
    {
        for (auto&& iter : m_DeviceMap)
        {
            delete iter.second;
        }
        m_DeviceMap.clear();
    }

    void InputManager::Update(float dt)
    {
        for (const auto& iter : m_DeviceMap)
        {
            iter.second->Update(dt);
        }

        m_InputEvents.clear();
        m_AxisEventsMap.clear();
        if (m_InputScheme != nullptr)
        {
            for (const auto& mapping : m_InputScheme->inputEventMappings)
            {
                bool keyValid = false;
                Vector2f axis;

                switch (mapping.inputType)
                {
                case CustomInputType::_Down:
                {
                    keyValid = GetBoolKeyDown(mapping.key);
                }break;
                case CustomInputType::_Release:
                {
                    keyValid = GetBoolKeyRelease(mapping.key);
                }break;
                case CustomInputType::_Click:
                {
                    keyValid = GetBoolKeyClick(mapping.key);
                }break;
                case CustomInputType::_Press:
                {
                    keyValid = GetBoolKeyPress(mapping.key, mapping.holdTime);
                }break;
                case CustomInputType::_Move:
                {
                    axis = GetAxisKey(mapping.key);
                }break;
                default:
                    LOG_WARNING("unhandle CustomInputType");
                }

                if (keyValid || axis != Vector2f::Zero())
                {
                    if (mapping.modifyKey1 != InputKey::_None)
                        keyValid = GetBoolKeyDown(mapping.modifyKey1) ? keyValid : false;

                    if (mapping.modifyKey2 != InputKey::_None)
                        keyValid = GetBoolKeyDown(mapping.modifyKey2) ? keyValid : false;

                    if (keyValid)
                    {
                        m_InputEvents.emplace_back(mapping.event);
                    }

                    if (axis != Vector2f::Zero())
                    {
                        m_AxisEventsMap.emplace(mapping.event, axis);
                    }
                }
            }
        }
    }

    void InputManager::DeleteDevice(DeviceId id)
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

    bool InputManager::GetBoolKeyClick(InputKey key)
    {
        for (auto& iter : m_DeviceMap)
        {
            if (iter.second->GetBoolKeyClick(key))
                return true;
        }
        return false;
    }

    bool InputManager::GetBoolKeyPress(InputKey key, float holdTime)
    {
        for (auto& iter : m_DeviceMap)
        {
            if (iter.second->GetBoolKeyPress(key, holdTime))
                return true;
        }
        return false;
    }

    Vector2f InputManager::GetAxisKey(InputKey key)
    {
        Vector2f ret = Vector2f::Zero();
        for (auto& iter : m_DeviceMap)
        {
            if (iter.second->GetAxisKey(key, OUT ret))
                return ret;
        }
        return ret;
    }
}