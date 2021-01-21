#include "ArcheType.hpp"
#include "NanoEngine/Client/ECS/Chunk.hpp"

namespace Nano
{
    ArcheType::ArcheType(ComponentTypeSet typeSet)
    {
        m_TypeSet = typeSet;
        InitLayout();
    }

    ArcheType::~ArcheType()
    {
        std::for_each(m_Chunks.begin(), m_Chunks.end(), [](Chunk* chunk) {delete chunk; });
        m_Chunks.clear();
        m_FreeChunk = nullptr;
    }

    size_t ArcheType::CreateComponentInstance()
    {
        size_t index = AllocFreeBuffer();
        Chunk* freeChunk = m_Chunks.back();
        for (const auto& type : m_TypeSet.m_Data)
        {

        }

        return index;
    }

    size_t ArcheType::AllocFreeBuffer()
    {
        if (IsChunksFull())
        {
            m_Chunks.push_back(new Chunk());
        }
        return m_StoredEntityCount++;
    }

    void* ArcheType::GetComponent(ComponentType cmptType, size_t index)
    {
        if (!m_TypeSet.Contains(cmptType))
            return nullptr;

        return nullptr;
    }

    void ArcheType::InitLayout()
    {
        Vector<size_t> alignments(m_TypeSet.Size());
        Vector<size_t> sizes(m_TypeSet.Size());

        for (const auto& cmptType : m_TypeSet.m_Data)
        {
            //alignments.push_back(alignof(cmptType));
            //sizes.push_back(sizeof(cmptType));
        }

        //Chunk::Init(alignments, sizes, m_TypeOffsets, m_ChunkCapacity);
    }

    inline bool ArcheType::IsChunksFull()
    {
        return m_Chunks.size() * m_ChunkCapacity <= m_StoredEntityCount;
    }
}
