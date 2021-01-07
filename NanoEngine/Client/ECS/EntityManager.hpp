#pragma once
#include "NanoEngine/Client/ECS/Entity.hpp"

namespace Nano
{
    class EntityManager
    {
    public:
        template<typename... T>
        void CreateEntity();
    };

    template<typename... T>
    void EntityManager::CreateEntity()
    {
        Entity entity;
        entity.m_Version++;
    }
}