#pragma once
#include "NanoEngine/Common/IRuntimeModule.hpp"
#include "Allocator.hpp"

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

        static constexpr uint16_t k_BlockSizes[] = {
            // 4-increments
            4,  8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48,
            52, 56, 60, 64, 68, 72, 76, 80, 84, 88, 92, 96,

            // 32-increments
            128, 160, 192, 224, 256, 288, 320, 352, 384,
            416, 448, 480, 512, 544, 576, 608, 640,

            // 64-increments
            704, 768, 832, 896, 960, 1024
        };

        static constexpr uint32_t k_NumBlockSize = sizeof(k_BlockSizes) / sizeof(k_BlockSizes[0]);
        static constexpr uint32_t k_MaxBlockSize = k_BlockSizes[k_NumBlockSize - 1];

    private:
        Allocator* LookUpAllocator(size_t size);
    };
}