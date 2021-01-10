#include "EntityManager.hpp"

namespace Nano
{
    EntityManager::~EntityManager()
    {
        std::for_each(m_EntityInfos.begin(), m_EntityInfos.end(), [](EntityInfo* info) {delete info; });
        m_EntityInfos.clear();
        m_FreeEntityInfo = nullptr;
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

