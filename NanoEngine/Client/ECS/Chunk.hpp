#pragma
#include "Common/Type/TypeDef.hpp"
#include "Common/Type/ArrayWrapper.hpp"
#include "Common/Type/MapWrapper.hpp"
#include "ComponentType.hpp"

namespace Nano
{
    class Chunk
    {
    public:
        static constexpr int32_t k_ChunkSize = 16 * 1024;
        ubyte* Data() { return m_Buffer.data(); }
    private:
        Array<ubyte, k_ChunkSize> m_Buffer;
    };
}