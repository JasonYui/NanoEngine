#include "ArcheTypeManager.hpp"
#include "NanoEngine/Client/ECS/ArcheType.hpp"
#include "NanoEngine/Client/ECS/Chunk.hpp"

namespace Nano
{
    void ArcheTypeManager::Clear()
    {
        for (auto&& item : m_TypeLookup)
        {
            std::for_each(item.second.begin(), item.second.end(), [](ArcheType* acheType) { delete acheType; });
            item.second.clear();
        }

        m_TypeLookup.clear();
    }
    Chunk* ArcheTypeManager::GetFreeChunk(ArcheType* archeType)
    {
        if (archeType->m_FreeChunk != nullptr)
            return archeType->m_FreeChunk;

        Chunk* chunk = new Chunk();
        chunk->Init(archeType);
        archeType->m_Chunks.push_back(chunk);
        archeType->m_FreeChunk = chunk;

        return chunk;
    }
}
