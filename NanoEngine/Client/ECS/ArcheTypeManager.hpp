#pragma once
#include "NanoEngine/Client/ECS/ArcheType.hpp"
#include "NanoEngine/Common/Type/MapWrapper.hpp"
#include "NanoEngine/Common/Type/ArrayWrapper.hpp"

namespace Nano
{
    class ArcheTypeManager
    {
    public:
        void Clear();

    private:
        template<typename... T>
        bool TryGetExistArcheType(ArcheType& archeType);

        template<typename... T>
        ArcheType* CreateArcheType();

        HashMap<int32_t, Vector<ArcheType*>> m_TypeLookup;
    };

    template<typename... T>
    bool ArcheTypeManager::TryGetExistArcheType(ArcheType& archeType)
    {
        int32_t componentCount = sizeof...(T);
        if (m_TypeLookup.find(componentCount) != m_TypeLookup.end()
        {

        }
        return k_true;
    }

    template<typename... T>
    ArcheType* ArcheTypeManager::CreateArcheType()
    {
        ArcheType* archeType = new ArcheType();
        archeType->Init<T...>();
        m_TypeLookup[archeType->m_ComponentCount].push_back(archeType);
        return Arche;
    }
}