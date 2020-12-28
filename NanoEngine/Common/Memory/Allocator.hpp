#pragma once

#include "NanoEngine/Common/Type/TypeDef.hpp"

namespace Nano
{
    struct BlockHeader
    {
        BlockHeader* next;
    };

    struct PageHeader
    {
        PageHeader* next;

        BlockHeader* Blocks()
        {
            return reinterpret_cast<BlockHeader*>(this + 1);
        }
    };

    class Allocator
    {
    public:
        // debug patterns
        static const uint8_t PATTERN_ALIGN = 0xFC;
        static const uint8_t PATTERN_ALLOC = 0xFD;
        static const uint8_t PATTERN_FREE = 0xFE;

        Allocator() = default;
        Allocator(size_t dataSize, size_t pageSize, size_t alignment);
        ~Allocator();

        void Reset(size_t dataSize, size_t pageSize, size_t alignment);
        void* Allocate();
        void Free(void* p);
        void FreeAll();

    private:
#if defined(_DEBUG)
        void FillFreePage(PageHeader* page);
        void FillFreeBlock(BlockHeader* block);
        void FillAllocatedBlock(BlockHeader* block);
#endif
        BlockHeader* NextBlock(BlockHeader* block);
        Allocator(const Allocator& clone) = delete;
        Allocator& operator=(const Allocator& rhs) = delete;

    private:
        PageHeader* m_PageList{ nullptr };
        BlockHeader* m_FreeList{ nullptr };
        size_t m_DataSize{ 0 };
        size_t m_PageSize{ 0 };
        size_t m_AlignmentSize{ 0 };
        size_t m_BlockSize{ 0 };
        uint32_t m_BlocksPerPage{ 0 };
        uint32_t m_PageCount{ 0 };
        uint32_t m_BlockCount{ 0 };
        uint32_t m_FreeBlockCount{ 0 };
    };
}