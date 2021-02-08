#pragma once
#include "Common/Fwd.hpp"
#include "Common/IRuntimeModule.hpp"
#include "Common/Type/MapWrapper.hpp"
#include "Common/Type/ArrayWrapper.hpp"
#include "Common/Type/MemoryWrapper.hpp"

#include "InputDefine.hpp"
#include "InputDevice.hpp"
#include "InputEnum.hpp"
#include "InputScheme.hpp"

namespace Nano
{
    class InputManager : IRuntimeModule
    {
    public:
        ~InputManager() {};
        bool Init() final { return true; };
        void Close() final;
        void Update(float dt) final;

        template<typename T>
        DeviceId CreateDevice() const;    //thread unsafe

        void DeleteDevice(DeviceId id);

        bool GetBoolKeyDown(InputKey key);
        bool GetBoolKeyRelease(InputKey key);
        bool GetBoolKeyClick(InputKey key);
        bool GetBoolKeyPress(InputKey key, float holdTime);
        Vector2f GetAxisKey(InputKey key);

        void SetInputScheme(SharedPtr<InputScheme> scheme) const { m_InputScheme = scheme; }

    private:
        mutable Map<DeviceId, InputDevice*> m_DeviceMap;
        mutable uint16_t m_NextDeviceIndex{ 0 };
        mutable SharedPtr<InputScheme> m_InputScheme;

        Vector<StringID> m_InputEvents;
        HashMap<StringID, Vector2f> m_AxisEventsMap;
    };

    template<typename T>
    DeviceId InputManager::CreateDevice() const
    {
        InputDevice* device = new T();
        InputDeviceType type = device->GetDeviceType();
        DeviceId id = (static_cast<uint32_t>(type) << 24) + m_NextDeviceIndex;
        m_DeviceMap.emplace(id, device);
        m_NextDeviceIndex++;
        return id;
    }
}