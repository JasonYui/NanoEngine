#pragma once
#include "common/fwd.hpp"
#include "common/runtime_module.hpp"
#include "common/type/map_wrapper.hpp"
#include "common/type/array_wrapper.hpp"
#include "common/type/memory_wrapper.hpp"

#include "client/input/input_define.hpp"
#include "client/input/input_device.hpp"
#include "client/input/input_enum.hpp"
#include "client/input/input_scheme.hpp"

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