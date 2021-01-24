#include "ArcheType.hpp"

namespace Nano
{
    ArcheType::~ArcheType()
    {
        std::for_each(m_Chunks.begin(), m_Chunks.end(), [](Chunk* chunk) {delete chunk; });
        m_Chunks.clear();
    }

    void ArcheType::Init(Set<CmptType> cmptTypeSet) //$todo check set contains IndexType
    {
        m_CmptTypeSet = std::move(cmptTypeSet);
        InitLayout();
    }

    bool ArcheType::IsSame(const CmptTypeSet& set) const
    {
        return m_CmptTypeSet == set;
    }

    size_t ArcheType::MoveCtor(ArcheType& srcArcheType, size_t idxInSrcArcheType)
    {
        size_t idxInArcheType = AllocFreeBuffer();
        for (auto& cmptType : m_CmptTypeSet)
        {
            auto iter = srcArcheType.m_TypeOffsetMap.find(cmptType);
            if (iter == srcArcheType.m_TypeOffsetMap.end())
                continue;

            ubyte* trgCmpt = GetComponent(cmptType, idxInArcheType);
            ubyte* srcCmpt = srcArcheType.GetComponent(cmptType, idxInSrcArcheType);
            assert(trgCmpt != nullptr);
            assert(srcCmpt != nullptr);

            memmove(trgCmpt, srcCmpt, cmptType.GetSize());
        }
        return idxInArcheType;
    }

    size_t ArcheType::AllocFreeBuffer()
    {
        if (IsChunksFull())
        {
            m_Chunks.push_back(new Chunk());
        }
        return m_StoredEntityCount++;
    }

    size_t ArcheType::DeleteCmptByIndex(size_t idxInArcheType)
    {
        size_t movedIdx = SIZE_MAX;
        size_t chunkIndex = idxInArcheType / m_ChunkCapacity;
        size_t localIndex = idxInArcheType % m_ChunkCapacity;
        assert(chunkIndex < m_Chunks.size());
        ubyte* locateBuffer = m_Chunks[chunkIndex]->Data();

        if (idxInArcheType == m_StoredEntityCount - 1) // is last entity components
        {
            for (const auto& cmptType : m_CmptTypeSet)
            {
                auto iter = m_TypeOffsetMap.find(cmptType);
                if (iter != m_TypeOffsetMap.end())
                {
                    ubyte* data = GetComponent(cmptType, idxInArcheType);
                    memset(data, 0, cmptType.GetSize()); // need ctor before delete
                }
            }
        }
        else
        {
            size_t movedIdxInArcheType = m_StoredEntityCount - 1;
            size_t movedLocalIdx = movedIdxInArcheType % m_ChunkCapacity;

            ubyte* srcBuffer = m_Chunks.back()->Data();

            for (const auto& cmptType : m_CmptTypeSet)
            {
                auto iter = m_TypeOffsetMap.find(cmptType);
                if (iter != m_TypeOffsetMap.end())
                {
                    ubyte* src = GetComponent(cmptType, movedIdxInArcheType);
                    assert(src != nullptr);

                    ubyte* trg = GetComponent(cmptType, idxInArcheType);
                    assert(trg != nullptr);
                    if (cmptType.IsType<IndexType>())
                    {
                        movedIdx = reinterpret_cast<IndexType*>(src)->index;
                    }

                    memmove(src, trg, cmptType.GetSize());
                }
            }

        }

        m_StoredEntityCount--;
        if (m_StoredEntityCount % m_ChunkCapacity == 0)
            m_Chunks.pop_back();

        return movedIdx;
    }

    ubyte* ArcheType::GetComponent(const CmptType& cmptType, size_t idxInArcheType)
    {
        assert(idxInArcheType < m_StoredEntityCount);

        auto iter = m_TypeOffsetMap.find(cmptType);
        if (iter != m_TypeOffsetMap.end())
        {
            size_t chunkIdx = idxInArcheType / m_ChunkCapacity;
            size_t idxInChunk = idxInArcheType % m_ChunkCapacity;
            assert(chunkIdx < m_Chunks.size());
            ubyte* locateBuffer = m_Chunks[chunkIdx]->Data();
            return locateBuffer + iter->second + idxInChunk * cmptType.GetSize();
        }
        return nullptr;
    }

    void ArcheType::InitLayout()
    {
        struct SortCmptType
        {
            CmptType cmptType;
            size_t index = 0;

            SortCmptType() = default;
            SortCmptType(CmptType _cmptType, size_t _index) : cmptType(_cmptType), index(_index) {};
            bool operator<(const SortCmptType& rhs) const noexcept
            {
                return cmptType.GetAlignment() < rhs.cmptType.GetAlignment();
            }
        };

        Vector<SortCmptType> sortCmptTyps(m_CmptTypeSet.size());
        Vector<size_t> sizes(m_CmptTypeSet.size());

        size_t index = 0;
        for (const auto& cmptType : m_CmptTypeSet)
        {
            sortCmptTyps[index] = SortCmptType{ CmptType(cmptType), index };
            sizes[index] = cmptType.GetSize();
            index++;
        }

        std::sort(sortCmptTyps.begin(), sortCmptTyps.end());

        size_t sumSize = 0;
        for (size_t s : sizes)
            sumSize += s;
        m_ChunkCapacity = Chunk::k_ChunkSize / sumSize;

        size_t curOffset = 0;
        for (size_t i = 0; i < sizes.size(); i++)
        {
            size_t alignment = sortCmptTyps[i].cmptType.GetAlignment();
            curOffset = alignment * ((curOffset + alignment - 1) / alignment);
            m_TypeOffsetMap.emplace(sortCmptTyps[i].cmptType, curOffset);
            curOffset += sizes[sortCmptTyps[i].index] * m_ChunkCapacity;
        }
    }
}
