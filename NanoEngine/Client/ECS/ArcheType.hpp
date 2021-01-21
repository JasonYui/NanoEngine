#pragma once
#include "NanoEngine/Common/Type/TypeDef.hpp"
#include "NanoEngine/Common/Type/ArrayWrapper.hpp"
#include "NanoEngine/Client/ECS/ComponentType.hpp"

namespace Nano
{
    class Chunk;

    class ArcheType
    {
        friend class ArcheTypeManager;
        friend class Chunk;
    public:
        ArcheType() = default;

        ArcheType(ComponentTypeSet typeSet);

        ~ArcheType();

        template<typename... TC>
        void Init();

        size_t CreateComponentInstance();

        const ComponentTypeSet& GetComponentTypeSet() const { return m_TypeSet; }

        template<typename T>
        int GetComponentIndex();

        size_t AllocFreeBuffer();

        void* GetComponent(ComponentType cmptType, size_t index);

        template<typename T>
        T* GetComponent(size_t index);
    private:
        void InitLayout();

        inline bool IsChunksFull();

        template<typename T>
        void InitImpl();

        template<typename T1, typename T2, typename... TC>
        void InitImpl();

        uint32_t m_ComponentCount{ 0 };
        size_t* m_TypeHashes;
        size_t* m_Offsets;
        size_t m_ComponentTotalSize{ 0 };

        ComponentTypeSet m_TypeSet;

        Vector<Chunk*> m_Chunks;
        Chunk* m_FreeChunk;

        size_t m_ChunkCapacity{ 0 };
        Vector<size_t> m_TypeOffsets;
        size_t m_StoredEntityCount{ 0 };
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