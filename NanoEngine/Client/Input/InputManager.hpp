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
        DeviceID CreateDevice();    //thread unsafe

        void DeleteDevice(DeviceID id);

        bool GetBoolKeyDown(Key key);
        bool GetBoolKeyRelease() {};

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
        Map<DeviceID, InputDevice*> m_DeviceMap;
        DeviceID m_NextDeviceID{0};
        Queue<Change> m_CurrentInputQueue;

        SharedPtr<InputScheme> m_InputScheme;
    };
}