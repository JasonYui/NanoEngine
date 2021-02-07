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
        virtual ~InputManager() {};
        virtual bool Init() { return true; };
        virtual void Close() {};
        void Update(float dt) override;

        template<typename T>
        DeviceID CreateDevice() const;    //thread unsafe

        const InputDevice* GetDevice(DeviceID id);

        void DeleteDevice(DeviceID id);

        bool GetBoolKeyDown(InputKey key);
        bool GetBoolKeyRelease(InputKey key);

    private:
        struct Change
        {
            InputDevice* device;
            union
            {
                bool b;
                float f;
            };
        };

    private:
        mutable Map<DeviceID, InputDevice*> m_DeviceMap;
        mutable uint16_t m_NextDeviceIndex{ 0 };
        Queue<Change> m_CurrentInputQueue;

        SharedPtr<InputScheme> m_InputScheme;
    };

    template<typename T>
    DeviceID InputManager::CreateDevice() const
    {
        T* device = new T();
        InputDeviceType type = device->GetDeviceType();
        DeviceID id = (static_cast<uint32_t>(type) << 24) + m_NextDeviceIndex;
        m_DeviceMap[id] = device;
        m_NextDeviceIndex++;
        return id;
    }
}