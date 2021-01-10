#include "ArcheType.hpp"
#include "NanoEngine/Client/ECS/Chunk.hpp"

namespace Nano
{
    ArcheType::~ArcheType()
    {
        std::for_each(m_Chunks.begin(), m_Chunks.end(), [](Chunk* chunk) {delete chunk; });
        m_Chunks.clear();
        m_FreeChunk = nullptr;
    }
}
