#pragma once
#include "NanoEngine/Client/ECS/Entity.hpp"
#include "NanoEngine/Client/ECS/ArcheTypeManager.hpp"
#include "Common/Type/MemoryWrapper.hpp"

namespace Nano
{
    class Chunk;

    class EntityManager
    {
    public:
        EntityManager(ArcheTypeManager* archeTypeManager) : m_ArcheTypeManager(archeTypeManager) {}

        ~EntityManager();

        template<typename... T>
        Entity CreateEntity();

        bool inline IsValid(const Entity& entity);

        void Detech(const Entity& entity, Span<ComponentType> components);

        void FreeEntity(const Entity& entity);
    private:
        struct EntityInfo
        {
            size_t index;
            size_t version;
            size_t indexInArcheType;
            ArcheType* archeType;
            EntityInfo* nextFreeEntityInfo;
        };

        EntityInfo* GetUnuseEntityInfo();

        Vector<EntityInfo*> m_EntityInfos;
        EntityInfo* m_FreeEntityInfo{ nullptr };
        const size_t k_InvalidVersion = SIZE_MAX;

        ArcheTypeManager* m_ArcheTypeManager;
    };

    template<typename... T>
    Entity EntityManager::CreateEntity()
    {
        EntityInfo* info = GetUnuseEntityInfo();
        Entity entity;
        entity.index = info->index;
        entity.version = info->version;
        m_FreeEntityInfo = m_FreeEntityInfo->nextFreeEntityInfo;

        ArcheType* archeType = m_ArcheTypeManager->GetArcheType<T...>();

        return entity;
    }
}