#pragma
#include "NanoEngine/Common/Type/TypeDef.hpp"

namespace Nano
{
    class ArcheType;

    class Chunk
    {
    public:
        Chunk();
        ~Chunk();
        bool Init(ArcheType* archeType);

    private:
        struct Property
        {
            alignas(8) ArcheType* archeType = nullptr;
            alignas(8) size_t unitCount = 0;
        };

        void* m_Buffer;
        Property* m_Property;
        void** m_ComponentList{ nullptr };

    };
}