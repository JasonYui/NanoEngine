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
        static void Init(const Vector<size_t>& alignments, const Vector<size_t>& sizes, OUT Vector<size_t>& offsets, OUT size_t& capacity);

        static constexpr int32_t k_ChunkSize = 16 * 1024;
        ubyte* Data() { return m_Buffer.data(); }
    private:
        struct AlignmentInfo
        {
            size_t alignment = 0;
            size_t index = 0;
            bool operator<(const AlignmentInfo& rhs) const noexcept
            {
                return alignment < rhs.alignment;
            }
        };

        Array<ubyte, k_ChunkSize> m_Buffer;

    };
}