#pragma once
#include <memory>
#include "NanoEngine/Common/IRuntimeModule.hpp"
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/class.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/mono-config.h>

namespace Nano
{
    class CSDelegate : IRuntimeModule
    {
    public:
        bool Init() final;
        void Close() final;
        void Update(float dt) final {};

    private:
        MonoDomain* m_Domain;
    };
}