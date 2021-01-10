#pragma once
#include "NanoEngine/Common/Type/TypeDef.hpp"
#include "NanoEngine/Common/Type/ArrayWrapper.hpp"

namespace Nano
{
    class Chunk;

    class ArcheType
    {
        friend class ArcheTypeManager;
        friend class Chunk;
    public:
        ~ArcheType();

        template<typename... TC>
        void Init();

        template<typename T>
        int GetComponentIndex();
    private:
        template<typename T>
        void InitImpl();

        template<typename T1, typename T2, typename... TC>
        void InitImpl();

        uint32_t m_ComponentCount{ 0 };
        size_t* m_TypeHashes;
        size_t* m_Offsets;
        size_t m_ComponentTotalSize{ 0 };

        Vector<Chunk*> m_Chunks;
        Chunk* m_FreeChunk;
    };

    template<typename... TC>
    void ArcheType::Init()
    {
        m_TypeHashes = new size_t[sizeof...(TC)]();
        m_Offsets = new size_t[sizeof...(TC)]();
        InitImpl<TC...>();
    }

    template<typename T>
    int ArcheType::GetComponentIndex()
    {
        size_t hash = typeid(T).hash_code();
        for (size_t i = 0; i < m_ComponentCount; i++)
        {
            if (hash == m_TypeHashes[i])
                return i;
        }
        return -1;
    }

    template<typename T>
    void ArcheType::InitImpl()
    {
        size_t hash = typeid(T).hash_code();
        int32_t i = m_ComponentCount - 1;
        for (i; i >= 0 && hash < m_TypeHashes[i]; i--)
        {
            m_TypeHashes[i + 1] = m_TypeHashes[i];
            m_Offsets[i + 1] = m_Offsets[i] + sizeof(T);
        }
        m_TypeHashes[i + 1] = hash;

        m_ComponentCount += 1;
        m_ComponentTotalSize += sizeof(T);
    }

    template<typename T1, typename T2, typename... TC>
    void ArcheType::InitImpl()
    {
        InitImpl<T1>();
        InitImpl<T2, TC...>();
    }
}