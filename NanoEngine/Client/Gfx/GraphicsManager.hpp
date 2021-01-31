#pragma once
#include "Common/IRuntimeModule.hpp"

namespace Nano
{
    _interface_ GraphicsManager : public IRuntimeModule
    {
    public:
        virtual ~GraphicsManager() = default;

        virtual bool Init() override = 0;
        virtual void Close() override = 0;
        virtual void Update(float dt) override = 0;
    };
}