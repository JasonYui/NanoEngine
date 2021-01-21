#include "EntityManager.hpp"
#include <stdexcept>

namespace Nano
{
    EntityManager::~EntityManager()
    {
        std::for_each(m_EntityInfos.begin(), m_EntityInfos.end(), [](EntityInfo* info) {delete info; });
        m_EntityInfos.clear();
        m_FreeEntityInfo = nullptr;

        delete m_ArcheTypeManager;
    }

    inline bool EntityManager::IsValid(const Entity& entity)
    {
        if (entity.index < m_EntityInfos.size())
        {
            return m_EntityInfos[entity.index]->version == entity.version;
        }
        return false;
    }

    void EntityManager::Detech(const Entity& entity, Span<ComponentType> components)
    {
        if (!IsValid(entity))
            throw std::invalid_argument("[EntityManager::Detech] entity is invalid");

        EntityInfo* info = m_EntityInfos[entity.index];
        ComponentTypeSet typeSet = info->archeType->GetComponentTypeSet();
        typeSet.Delete(components);
        ArcheType* archeType = m_ArcheTypeManager->GetArcheType(typeSet);
        typeSet.Foreach([&](auto type) {});
    }

    void EntityManager::FreeEntity(const Entity& entity)
    {
        if (m_EntityInfos.size() > entity.index)
        {
            EntityInfo* info = m_EntityInfos[entity.index];
            if (info->version == entity.version)
            {
                info->version++;
                if (info->version != k_InvalidVersion)
                {
                    info->nextFreeEntityInfo = m_FreeEntityInfo;
                    m_FreeEntityInfo = info;
                }
            }
        }
    }

    EntityManager::EntityInfo* EntityManager::GetUnuseEntityInfo()
    {
        if (m_FreeEntityInfo == nullptr)
        {
            m_FreeEntityInfo = new EntityInfo();
            m_FreeEntityInfo->nextFreeEntityInfo = nullptr;
            m_EntityInfos.push_back(m_FreeEntityInfo);
        }
        return m_FreeEntityInfo;
    }
}

