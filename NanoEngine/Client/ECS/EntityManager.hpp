#pragma once
#include "Entity.hpp"
#include "ArcheType.hpp"
#include <stdexcept>
#include <functional>

namespace Nano
{
    class EntityManager
    {
    public:
        EntityManager() = default;

        ~EntityManager();

        /// <summary>
        /// create entity with component type
        /// </summary>
        /// <typeparam name="...TC"></typeparam>
        /// <returns>Entity</returns>
        template<typename... TC>
        Entity CreateEntity();

        template<typename T>
        T* GetComponent(const Entity& entity);

        bool IsSameArcheType(const Entity& lhs, const Entity& rhs);

        bool IsValid(const Entity& entity);

        template<typename TC, typename... Args>
        void Attach(const Entity& entity, Args&&... args);

        template<typename T1, typename T2, typename... TC>
        void Attach(const Entity& entity);

        template<typename... TC>
        void Detach(const Entity& entity);

        void FreeEntity(const Entity& entity);

        template<typename... TC>
        void Foreach(std::function<void(Entity entity, TC*... cmpts)> func);

        static constexpr size_t k_InvalidVersion = SIZE_MAX;
    private:
        struct EntityInfo
        {
            size_t index;
            size_t version;
            size_t idxInArcheType;
            ArcheType* archeType;
            EntityInfo* nextFreeEntityInfo;
        };

        using CmptTypeSet = Set<CmptType>;
    private:
        template<typename... TC>
        ArcheType* GetArcheType();
        ArcheType* GetArcheType(CmptTypeSet set);

        template<typename... TC>
        ArcheType* CreateArcheType();
        ArcheType* CreateArcheType(const CmptTypeSet& set);

        template<typename... TC>
        ArcheType* GetExistArcheType();
        ArcheType* GetExistArcheType(const CmptTypeSet& set);

        EntityInfo* GetUnuseEntityInfo();

    private:
        HashMap<size_t, Vector<ArcheType*>> m_ArcheTypeLookup;
        Vector<EntityInfo*> m_EntityInfos;
        EntityInfo* m_FreeEntityInfo{ nullptr };
    };
}

#include "Details/EntityManager.inl"