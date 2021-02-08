#pragma once
#include "InputState.hpp"
#include "InputEnum.hpp"

namespace Nano
{
    class InputDevice
    {
    public:
        virtual ~InputDevice()
        {
            delete m_State;
            m_State = nullptr;

            delete m_PrevState;
            m_PrevState = nullptr;
        }

        virtual void Update(float dt) = 0;

        virtual InputDeviceType inline GetDeviceType() const = 0;

        virtual bool GetBoolKeyDown(InputKey key) = 0;

        virtual bool GetBoolKeyRelease(InputKey key) = 0;

        virtual bool GetBoolKeyClick(InputKey key) = 0;

        virtual bool GetBoolKeyPress(InputKey key, float holdTime) = 0;

        virtual bool GetAxisKey(InputKey key, OUT Vector2f& axis) = 0;

    protected:
        InputState* m_State;
        InputState* m_PrevState;
    };
}