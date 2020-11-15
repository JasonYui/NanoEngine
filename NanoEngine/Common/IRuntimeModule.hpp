#pragma once

#include "NanoEngine/Common/Type/BasicType.hpp"

namespace Nano
{
    _interface_ IRuntimeModule
    {
    public :
        virtual ~IRuntimeModule() {};
        virtual bool Init() = 0;
        virtual void Close() = 0;
        virtual void Update(float dt) = 0;
    };
}