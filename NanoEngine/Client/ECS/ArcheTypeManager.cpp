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

    ArcheType* ArcheTypeManager::GetArcheType(ComponentTypeSet typeSet)
    {
        ArcheType* archeType = GetExistArcheType(typeSet);
        if (archeType == nullptr)
            archeType = CreateArcheType(typeSet);

        assert(archeType != nullptr);
        return archeType;
    }

    ArcheType* ArcheTypeManager::GetExistArcheType(const ComponentTypeSet& typeSet)
    {
        if (m_TypeLookup.find(typeSet.Size()) != m_TypeLookup.end())
        {
            for (auto item : m_TypeLookup[typeSet.Size()])
            {
                if (IsArcheTypeMatch(item, typeSet))
                    return item;
            }
        }
        return nullptr;
    }
    bool ArcheTypeManager::IsArcheTypeMatch(ArcheType* archeType, const ComponentTypeSet& typeSet)
    {
        return archeType->GetComponentTypeSet() == typeSet;
    }

    ArcheType* ArcheTypeManager::CreateArcheType(const ComponentTypeSet& typeSet)
    {
        ArcheType* archeType = new ArcheType(typeSet);
        m_TypeLookup[archeType->m_ComponentCount].push_back(archeType);
        return archeType;
    }
}
