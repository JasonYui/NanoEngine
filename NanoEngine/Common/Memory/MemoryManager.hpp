#pragma once
#include "NanoEngine/Common/IRuntimeModule.hpp"

namespace Nano
{
    class MemoryManager : IRuntimeModule
    {
    public:
        MemoryManager();
        ~MemoryManager();

        bool Init();
        void Close();
        void Update(float dt);

    private:

    };
}