#pragma once
#include "NanoEngine/Common/Type/MapWrapper.hpp"
#include "NanoEngine/Common/Type/ArrayWrapper.hpp"

namespace Nano
{
    class Chunk;
    class ArcheType;

    class ArcheTypeManager
    {
    public:
        void Clear();

        template<typename... T>
        ArcheType* GetArcheType();

        Chunk* GetFreeChunk(ArcheType* archeType);
    private:
        template<typename... T>
        ArcheType* TryGetExistArcheType();

        template<typename... T>
        bool IsArcheTypeMatch(const ArcheType& archeType);

        template<typename T>
        void GetTypeHashes(size_t* hashes, int32_t size);

        template<typename T1, typename T2, typename... TS>
        void GetTypeHashes(size_t* hashes, int32_t size);

        template<typename... T>
        ArcheType* CreateArcheType();

        HashMap<int32_t, Vector<ArcheType*>> m_TypeLookup;
    };

    template<typename... T>
    ArcheType* ArcheTypeManager::GetArcheType()
    {
        ArcheType* archeType = TryGetExistArcheType<T...>();
        if (archeType != nullptr)
            return archeType;

        return CreateArcheType<T...>();
    }

    template<typename... T>
    ArcheType* ArcheTypeManager::TryGetExistArcheType()
    {
        int32_t componentCount = sizeof...(T);
        if (m_TypeLookup.find(componentCount) != m_TypeLookup.end())
        {
            for (auto item : m_TypeLookup[componentCount])
            {
                if (IsArcheTypeMatch<T...>(*item))
                    return item;
            }
        }
        return nullptr;
    }

    template<typename... T>
    ArcheType* ArcheTypeManager::CreateArcheType()
    {
        ArcheType* archeType = new ArcheType();
        archeType->Init<T...>();
        m_TypeLookup[archeType->m_ComponentCount].push_back(archeType);
        return archeType;
    }

    template<typename... T>
    bool ArcheTypeManager::IsArcheTypeMatch(const ArcheType& archeType)
    {
        int32_t size = sizeof...(T);
        if (archeType.m_ComponentCount != size)
            return false;

        size_t* tempHashes = new size_t[size]();
        GetTypeHashes<T...>(tempHashes, size);
        for (int32_t i = 0; i < size; ++i)
        {
            if (archeType.m_TypeHashes[i] != tempHashes[i])
                return false;
        }

        return true;
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