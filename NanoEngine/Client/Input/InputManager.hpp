#pragma once
#include "Common/IRuntimeModule.hpp"
#include "Common/Fwd.hpp"

namespace Nano
{
    class InputManager : IRuntimeModule
    {
    public:
        virtual ~InputManager() {};
        virtual bool Init() = 0;
        virtual void Close() = 0;
        virtual void Update(float dt) = 0;

    private:
    };
}