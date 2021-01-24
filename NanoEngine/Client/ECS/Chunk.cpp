#include "Chunk.hpp"
#include <iostream>

namespace Nano
{
    void Chunk::Init(const Vector<size_t>& alignments, const Vector<size_t>& sizes, OUT Vector<size_t>& offsets, OUT size_t& capacity)
    {
        assert(alignments.size() == sizes.size());
        Vector<AlignmentInfo> infos(alignments.size());
        size_t index = 0;
        for (const auto& item : alignments)
        {
            infos[index] = AlignmentInfo{ alignments [index], index };
            index++;
        }

        std::sort(infos.begin(), infos.end());

        size_t sumSize = 0;
        for (size_t s : sizes)
            sumSize += s;
        capacity = Chunk::k_ChunkSize / sumSize;

        offsets.reserve(alignments.size());
        size_t curOffset = 0;
        for (size_t i = 0; i < sizes.size(); i++)
        {
            curOffset = infos[i].alignment * ((curOffset + infos[i].alignment - 1) / infos[i].alignment);
            offsets[infos[i].index] = curOffset;
            curOffset += sizes[infos[i].index] * capacity;
        }
    }
}

