#pragma once
#include "NanoEngine/Client/ECS/Entity.hpp"
#include "NanoEngine/Client/ECS/ArcheTypeManager.hpp"

namespace Nano
{
    class Chunk;

    class EntityManager
    {
    public:
        ~EntityManager();

        template<typename... T>
        Entity CreateEntity(ArcheTypeManager* archeTypeManager);

        void FreeEntity(const Entity& entity);
    private:
        struct EntityInfo
        {
            size_t index;
            size_t version;
            EntityInfo* nextFreeEntityInfo;
        };

        EntityInfo* GetUnuseEntityInfo();

        Vector<EntityInfo*> m_EntityInfos;
        EntityInfo* m_FreeEntityInfo{ nullptr };
        const size_t k_InvalidVersion = SIZE_MAX;
    };

    template<typename... T>
    Entity EntityManager::CreateEntity(ArcheTypeManager* archeTypeManager)
    {
        EntityInfo* info = GetUnuseEntityInfo();
        Entity entity;
        entity.index = info->index;
        entity.version = info->version;
        m_FreeEntityInfo = m_FreeEntityInfo->nextFreeEntityInfo;

        ArcheType* archeType = archeTypeManager->GetArcheType<T...>();
        Chunk* chunk = archeTypeManager->GetFreeChunk(archeType);

        return entity;
    }
}