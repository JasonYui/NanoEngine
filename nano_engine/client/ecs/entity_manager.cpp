#include "client/ecs/entity_manager.hpp"

namespace Nano
{
    EntityManager::~EntityManager()
    {
        std::for_each(m_EntityInfos.begin(), m_EntityInfos.end(), [](EntityInfo* info) {delete info; });
        m_EntityInfos.clear();
        m_FreeEntityInfo = nullptr;

        for (auto&& item : m_ArcheTypeLookup)
        {
            std::for_each(item.second.begin(), item.second.end(), [](ArcheType* acheType) { delete acheType; });
            item.second.clear();
        }

        m_ArcheTypeLookup.clear();
    }

    bool EntityManager::IsSameArcheType(const Entity& lhs, const Entity& rhs)
    {
        if (IsValid(lhs) && IsValid(rhs))
        {
            return m_EntityInfos[lhs.index]->archeType == m_EntityInfos[rhs.index]->archeType;
        }
        return false;
    }

    bool EntityManager::IsValid(const Entity& entity)
    {
        if (entity.index < m_EntityInfos.size())
        {
            return m_EntityInfos[entity.index]->version == entity.version;
        }
        return false;
    }

    void EntityManager::FreeEntity(const Entity& entity)
    {
        if (m_EntityInfos.size() > entity.index)
        {
            EntityInfo* info = m_EntityInfos[entity.index];
            if (info->version == entity.version)
            {
                //$todo how to dtor components
                size_t movedIndex = info->archeType->DeleteCmptByIndex(info->idxInArcheType);
                if (movedIndex != SIZE_MAX)
                {
                    m_EntityInfos[movedIndex]->idxInArcheType = info->idxInArcheType;
                }
                info->version++;
                if (info->version != k_InvalidVersion)
                {
                    info->nextFreeEntityInfo = m_FreeEntityInfo;
                    m_FreeEntityInfo = info;
                }
            }
        }
    }

    ArcheType* EntityManager::GetArcheType(CmptTypeSet set)
    {
        ArcheType* archeType = GetExistArcheType(set);
        if (archeType == nullptr)
            archeType = CreateArcheType(set);
        return archeType;
    }

    ArcheType* EntityManager::CreateArcheType(const CmptTypeSet& set)
    {
        ArcheType* archeType = new ArcheType();
        archeType->Init(set);
        m_ArcheTypeLookup[archeType->GetComponentCount()].push_back(archeType);
        return archeType;
    }

    ArcheType* EntityManager::GetExistArcheType(const CmptTypeSet& set)
    {
        auto iter = m_ArcheTypeLookup.find(set.size() - 1);
        if (iter != m_ArcheTypeLookup.end())
        {
            for (auto archeType : iter->second)
            {
                if (archeType->IsSame(set))
                {
                    return archeType;
                }
            }
        }

        return nullptr;
    }

    EntityManager::EntityInfo* EntityManager::GetUnuseEntityInfo()
    {
        if (m_FreeEntityInfo == nullptr)
        {
            m_FreeEntityInfo = new EntityInfo();
            m_FreeEntityInfo->index = m_EntityInfos.size();
            m_FreeEntityInfo->nextFreeEntityInfo = nullptr;
            m_EntityInfos.push_back(m_FreeEntityInfo);
        }
        return m_FreeEntityInfo;
    }
}

