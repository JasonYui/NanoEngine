#include "allocator.hpp"
#include "common/fwd.hpp"
#include "common/math/math.hpp"

using namespace Nano;

namespace Nano
{
    Allocator::Allocator(size_t dataSize, size_t pageSize, size_t alignment)
    {
        Reset(dataSize, pageSize, alignment);
    }

    Allocator::~Allocator()
    {
        FreeAll();
    }

    void Allocator::Reset(size_t dataSize, size_t pageSize, size_t alignment)
    {
        FreeAll();

        m_DataSize = dataSize;
        m_PageSize = pageSize;

        size_t minSize = (sizeof(BlockHeader) > m_DataSize) ? sizeof(BlockHeader) : m_DataSize;
        // this magic only works when alignment is 2^n, which should general be the case
        // because most CPU/GPU also requires the aligment be in 2^n
        // but still we use a assert to guarantee it
#ifdef ENGINE_DEBUG
        ASSERT(alignment > 0 && (alignment & (alignment - 1)) == 0);
#endif
        m_BlockSize = Math::Align(minSize, alignment);

        m_AlignmentSize = m_BlockSize - minSize;

        m_BlocksPerPage = static_cast<uint32_t>((m_PageSize - sizeof(PageHeader)) / m_BlockSize);
    }

    void* Allocator::Allocate()
    {
        if (!m_FreeList)
        {
            PageHeader* newPage = reinterpret_cast<PageHeader*>(malloc(m_PageSize));
            ++m_PageCount;
            m_BlockCount += m_BlocksPerPage;
            m_FreeBlockCount += m_BlocksPerPage;

#ifdef ENGINE_DEBUG
            FillFreePage(newPage);
#endif

            if (m_PageList)
            {
                newPage->next = m_PageList;
            }

            m_PageList = newPage;

            BlockHeader* block = newPage->Blocks();
            // link each block in the page
            for (uint32_t i = 0; i < m_BlocksPerPage - 1; i++)
            {
                block->next = NextBlock(block);
                block = NextBlock(block);
            }
            block->next = nullptr;

            m_FreeList = newPage->Blocks();
        }

        BlockHeader* freeBlock = m_FreeList;
        m_FreeList = m_FreeList->next;
        --m_FreeBlockCount;

#if defined(_DEBUG)
        FillAllocatedBlock(freeBlock);
#endif

        return reinterpret_cast<void*>(freeBlock);
    }

    void Allocator::Free(void* p)
    {
        BlockHeader* block = reinterpret_cast<BlockHeader*>(p);

#if defined(_DEBUG)
        FillFreeBlock(block);
#endif

        block->next = m_FreeList;
        m_FreeList = block;
        ++m_FreeBlockCount;
    }

    void Allocator::FreeAll()
    {
        PageHeader* page = m_PageList;
        while (page)
        {
            PageHeader* p = page;
            page = page->next;

            delete[] reinterpret_cast<uint8_t*>(p);
        }

        m_PageList = nullptr;
        m_FreeList = nullptr;

        m_PageCount = 0;
        m_BlockCount = 0;
        m_FreeBlockCount = 0;
    }

#if defined(_DEBUG)

    void Allocator::FillFreePage(PageHeader* page)
    {
        page->next = nullptr;

        BlockHeader* block = page->Blocks();
        for (uint32_t i = 0; i < m_BlocksPerPage; i++)
        {
            FillFreeBlock(block);
            block = NextBlock(block);
        }
    }

    void Allocator::FillFreeBlock(BlockHeader* block)
    {
        std::memset(block, PATTERN_FREE, m_BlockSize - m_AlignmentSize);

        // alignment
        std::memset(reinterpret_cast<uint8_t*>(block) + m_BlockSize - m_AlignmentSize, PATTERN_ALIGN, m_AlignmentSize);
    }

    void Allocator::FillAllocatedBlock(BlockHeader* block)
    {
        std::memset(block, PATTERN_ALLOC, m_BlockSize - m_AlignmentSize);
        std::memset(reinterpret_cast<uint8_t*>(block) + m_BlockSize - m_AlignmentSize, PATTERN_ALIGN, m_AlignmentSize);
    }

#endif

    BlockHeader* Allocator::NextBlock(BlockHeader* block)
    {
        return reinterpret_cast<BlockHeader*>(reinterpret_cast<uint8_t*>(block) + m_BlockSize);
    }
}