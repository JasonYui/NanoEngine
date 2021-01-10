#include "Chunk.hpp"
#include <malloc.h>
#include <new>
#include "NanoEngine/Common/Type/TypeDef.hpp"
#include "NanoEngine/Client/ECS/ArcheType.hpp"
#include <iostream>

namespace Nano
{
    Chunk::Chunk()
    {
        m_Buffer = malloc(16 * 1024);//each chunk has 16KB
        m_Property = new(m_Buffer)Property();
    }

    Chunk::~Chunk()
    {
        free(m_Buffer);
    }

    //------------------------
    //c0 ---------------------
    //c1 ---------------------
    //c2 ---------------------
    //------------------------

    bool Chunk::Init(ArcheType* archeType)
    {
        m_Property->archeType = archeType;
        m_Property->unitCount = (16 * 1024 - sizeof(Property)) / archeType->m_ComponentTotalSize;
        m_ComponentList = new void* [archeType->m_ComponentCount];
        m_ComponentList[0] = reinterpret_cast<uint8_t*>(m_Property) + sizeof(Property);
        uint8_t* startPtr = reinterpret_cast<uint8_t*>(m_ComponentList[0]);

        for (uint32_t i = 0; i < archeType->m_ComponentCount; ++i)
        {
            auto q = archeType->m_Offsets[i];
            std::cout << m_ComponentList[i] << std::endl;
        }
        for (uint32_t i = 0; i < archeType->m_ComponentCount; ++i)
        {
            m_ComponentList[i] = reinterpret_cast<void*>(startPtr + (m_Property->unitCount * archeType->m_Offsets[i]));
            std::cout << m_ComponentList[i] << std::endl;
        }
        return false;
    }
}

