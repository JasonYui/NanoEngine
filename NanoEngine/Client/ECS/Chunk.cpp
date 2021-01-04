#include "Chunk.hpp"
#include <malloc.h>

namespace Nano
{
    Chunk::Chunk()
    {
        void* buffer = malloc(16 * 1024);//each chunk has 16KB
    }
}

