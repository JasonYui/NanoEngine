namespace Nano
{
    template<typename... TC>
    Entity EntityManager::CreateEntity()
    {
        EntityInfo* info = GetUnuseEntityInfo();
        Entity entity;
        entity.index = info->index;
        entity.version = info->version;
        m_FreeEntityInfo = m_FreeEntityInfo->nextFreeEntityInfo;

        ArcheType* archeType = GetArcheType<TC...>();
        info->archeType = archeType;
        info->idxInArcheType = archeType->Ctor<TC...>(entity.index);

        return entity;
    }

    template<typename T>
    T* EntityManager::GetComponent(const Entity& entity)
    {
        if (!IsValid(entity))
            LOG_ERROR("[{0}] entity is invalid", __FUNCTION__);

        EntityInfo* info = m_EntityInfos[entity.index];
        return info->archeType->GetComponent<T>(info->idxInArcheType);
    }

    template<typename TC, typename... Args>
    void EntityManager::Attach(const Entity& entity, Args... args)
    {
        if (!IsValid(entity))
            LOG_ERROR("[{0}] entity is invalid", __FUNCTION__);

        EntityInfo* info = m_EntityInfos[entity.index];
        ArcheType* srcArcheType = info->archeType;
        if (srcArcheType != nullptr && !srcArcheType->IsCmptTypeValid<TC>())
        {
            Set<CmptType> copyTypeSet = info->archeType->GetCmptTypeSet();
            copyTypeSet.emplace(CmptType::Of<TC>());

            ArcheType* dstArcheType = GetArcheType(copyTypeSet);
            // move ctor
            info->idxInArcheType = dstArcheType->MoveCtor(*srcArcheType, info->idxInArcheType);
            dstArcheType->CustomCtorOnChunk<TC, Args...>(info->index, args...);
            info->archeType = dstArcheType;

            size_t movedIndex = srcArcheType->DeleteCmptByIndex(info->idxInArcheType);
            if (movedIndex != SIZE_MAX)
            {
                m_EntityInfos[movedIndex]->idxInArcheType = info->idxInArcheType;
            }
        }
    }

    template<typename T1, typename T2, typename... TC>
    void EntityManager::Attach(const Entity& entity)
    {
        if (!IsValid(entity))
            LOG_ERROR("[{0}] entity is invalid", __FUNCTION__);

        EntityInfo* info = m_EntityInfos[entity.index];
        ArcheType* srcArcheType = info->archeType;
        if (srcArcheType != nullptr && !srcArcheType->IsCmptTypeValid<TC...>())
        {
            Set<CmptType> copyTypeSet = info->archeType->GetCmptTypeSet();
            (copyTypeSet.emplace(CmptType::Of<TC>()), ...);

            ArcheType* dstArcheType = GetArcheType(copyTypeSet);
            // move ctor
            info->idxInArcheType = dstArcheType->MoveCtor(*srcArcheType, info->idxInArcheType);
            dstArcheType->DefaultCtorOnChunk<T1, T2, TC...>(info->index);
            info->archeType = dstArcheType;

            size_t movedIndex = srcArcheType->DeleteCmptByIndex(info->idxInArcheType);
            if (movedIndex != SIZE_MAX)
            {
                m_EntityInfos[movedIndex]->idxInArcheType = info->idxInArcheType;
            }
        }
    }

    template<typename... TC>
    void EntityManager::Detach(const Entity& entity)
    {
        if (!IsValid(entity))
            LOG_ERROR("[{0}] entity is invalid", __FUNCTION__);

        EntityInfo* info = m_EntityInfos[entity.index];
        ArcheType* srcArcheType = info->archeType;
        if (srcArcheType != nullptr && srcArcheType->IsCmptTypeValid<TC...>())
        {
            Set<CmptType> copyTypeSet = info->archeType->GetCmptTypeSet();
            (copyTypeSet.erase(CmptType::Of<TC>()), ...);

            if (copyTypeSet.size() > 1) // default contains IndexType
            {
                ArcheType* dstArcheType = GetArcheType(copyTypeSet);
                // move ctor
                info->idxInArcheType = dstArcheType->MoveCtor(*srcArcheType, info->idxInArcheType);
                info->archeType = dstArcheType;
            }

            srcArcheType->DtorOnChunk<TC...>(info->idxInArcheType);

            size_t movedIndex = srcArcheType->DeleteCmptByIndex(info->idxInArcheType);
            if (movedIndex != SIZE_MAX)
            {
                m_EntityInfos[movedIndex]->idxInArcheType = info->idxInArcheType;
            }
        }
    }

    template<typename... TC>
    void EntityManager::Foreach(std::function<void(Entity entity, TC*... cmpts)> func)
    {
        size_t cmptSize = sizeof...(TC);
        for (auto& iter : m_ArcheTypeLookup)
        {
            if (cmptSize > iter.first)
                continue;

            for (auto archeType : iter.second)
            {
                if (archeType->ContainsAll<TC...>())
                {
                    for (size_t i = 0; i < archeType->m_StoredEntityCount; ++i)
                    {
                        ArcheType::IndexType* idxType = archeType->GetComponent<ArcheType::IndexType>(i);
                        if (idxType != nullptr)
                        {
                            EntityInfo* info = m_EntityInfos[idxType->index];
                            Entity entity = Entity(info->index, info->version);
                            func(entity, archeType->GetComponent<TC>(i)...);
                        }
                    }
                }
            }
        }
    }

    template<typename... TC>
    ArcheType* EntityManager::GetArcheType()
    {
        ArcheType* archeType = GetExistArcheType<TC...>();
        if (archeType == nullptr)
            archeType = CreateArcheType<TC...>();
        return archeType;
    }

    template<typename... TC>
    ArcheType* EntityManager::CreateArcheType()
    {
        ArcheType* archeType = new ArcheType();
        archeType->Init<TC...>();
        m_ArcheTypeLookup[archeType->GetComponentCount()].push_back(archeType);
        return archeType;
    }

    template<typename... TC>
    ArcheType* EntityManager::GetExistArcheType()
    {
        auto pair = m_ArcheTypeLookup.find(sizeof...(TC));
        if (pair != m_ArcheTypeLookup.end())
        {
            for (auto archeType : pair->second)
            {
                if (archeType->IsSame<TC...>())
                {
                    return archeType;
                }
            }
        }

        return nullptr;
    }
}