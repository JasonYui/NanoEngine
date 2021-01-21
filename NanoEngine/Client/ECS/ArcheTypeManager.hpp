#pragma once
#include "NanoEngine/Common/Type/MapWrapper.hpp"
#include "NanoEngine/Common/Type/ArrayWrapper.hpp"
#include "NanoEngine/Client/ECS/ArcheType.hpp"

namespace Nano
{
    class Chunk;

    class ArcheTypeManager
    {
    public:
        void Clear();

        ArcheType* GetArcheType(ComponentTypeSet typeSet);

        template<typename... T>
        ArcheType* GetArcheType();
    private:
        ArcheType* GetExistArcheType(const ComponentTypeSet& typeSet);

        bool inline IsArcheTypeMatch(ArcheType* archeType, const ComponentTypeSet& typeSet);

        template<typename T>
        void GetTypeHashes(size_t* hashes, int32_t size);

        template<typename T1, typename T2, typename... TS>
        void GetTypeHashes(size_t* hashes, int32_t size);

        ArcheType* CreateArcheType(const ComponentTypeSet& typeSet);

        HashMap<size_t, Vector<ArcheType*>> m_TypeLookup;
    };

    template<typename... T>
    ArcheType* ArcheTypeManager::GetArcheType()
    {
        constexpr std::array types = { ComponentType::Of<T>()... };
        ComponentTypeSet typeSet;
        typeSet.Insert(std::span{ types });
        return GetArcheType(typeSet);
    }

    template<typename T>
    void ArcheTypeManager::GetTypeHashes(size_t* hashes, int32_t size)
    {
        size_t hash = typeid(T).hash_code();
        int32_t i = size - 2;
        for (i; i >= 0 && hash < hashes[i]; i--)
        {
            hashes[i + 1] = hashes[i];
        }
        hashes[i + 1] = hash;
    }

    template<typename T1, typename T2, typename... TS>
    void ArcheTypeManager::GetTypeHashes(size_t* hashes, int32_t size)
    {
        GetTypeHashes<T1>(hashes, size - sizeof...(TS) - 1);
        GetTypeHashes<T2, TS...>(hashes, size);
    }
}