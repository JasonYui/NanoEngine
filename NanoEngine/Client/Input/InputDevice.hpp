#pragma once
#include "InputState.hpp"
#include "InputEnum.hpp"

namespace Nano
{
    class InputDevice
    {
    public:
        virtual void Update(float dt) = 0;

        virtual InputDeviceType inline GetDeviceType() const = 0;

        virtual bool GetBoolKeyDown(Key key) = 0;

        virtual bool GetBoolKeyRelease(Key key) = 0;

        virtual bool GetBoolKeyClick(Key key) = 0;

        virtual bool GetBoolKeyPress(Key key, float holdTime) = 0;

    private:
        InputState* m_State;
        InputState* m_PrevState;
    };
}