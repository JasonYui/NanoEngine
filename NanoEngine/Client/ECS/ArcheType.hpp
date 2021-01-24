#pragma once
#include "Common/Type/TypeDef.hpp"
#include "Common/Type/ArrayWrapper.hpp"
#include "Client/ECS/ComponentType.hpp"
#include "Chunk.hpp"
#include <cassert>
#include <new>
#include <stdexcept>


namespace Nano
{
    class ArcheType
    {
        friend class EntityManager;
        friend class Chunk;

        using CmptTypeSet = Set<CmptType>;
    public:
        ArcheType() = default;
        ~ArcheType();

        template<typename... TC>
        inline void Init();
        void Init(Set<CmptType> cmptTypeSet);

        template<typename... TC>
        bool inline IsSame() const;
        bool IsSame(const CmptTypeSet& set) const;

        template<typename... TC>
        bool ContainsAll() const;

        /// <summary>
        /// construct components on arche type by default contructor
        /// </summary>
        /// <typeparam name="...TC"></typeparam>
        /// <param name="entityIdx"></param>
        /// <returns>index in ArcheType</returns>
        template<typename T1, typename T2, typename... TC>
        size_t inline Ctor(size_t entityIdx);

        template<typename T1, typename T2, typename... TC>
        void DefaultCtorOnChunk(size_t indexInChunk);

        template<typename T, typename... Args>
        void inline CustomCtorOnChunk(size_t indexInChunk, Args... args);

        /// <summary>
        /// move components from source arche type
        /// </summary>
        /// <param name="srcArcheType"></param>
        /// <param name="idxInSrcArcheType"></param>
        /// <returns>index in ArcheType</returns>
        size_t MoveCtor(ArcheType& srcArcheType, size_t idxInSrcArcheType);

        template<typename TC>
        void DtorOnChunk(size_t idxInArcheType);

        /// <summary>
        /// dctor components on chunk, call DeleteCmptByIndex after
        /// </summary>
        /// <typeparam name="T1"></typeparam>
        /// <typeparam name="T2"></typeparam>
        /// <typeparam name="...TC"></typeparam>
        /// <param name="idxInArcheType"></param>
        template<typename T1, typename T2, typename... TC>
        void DtorOnChunk(size_t idxInArcheType);

        template<typename... TC>
        bool inline IsCmptTypeValid() const;

        const CmptTypeSet& GetCmptTypeSet() const { return m_CmptTypeSet; }

        size_t GetComponentCount() const { return m_CmptTypeSet.size() - 1; }

        /// <summary>
        /// delete component instance, make sure dtor or move data before delete
        /// </summary>
        /// <param name="idxInArcheType"></param>
        /// <returns> moved entity index </returns>
        size_t DeleteCmptByIndex(size_t idxInArcheType);

        /// <summary>
        /// get point to component instance
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="idxInArcheType"></param>
        /// <returns>T*</returns>
        template<typename T>
        T* GetComponent(size_t idxInArcheType);

        /// <summary>
        /// get point to component instance
        /// </summary>
        /// <param name="cmptType"></param>
        /// <param name="idxInArcheType"></param>
        /// <returns>ubyte*</returns>
        ubyte* GetComponent(const CmptType& cmptType, size_t idxInArcheType);
    private:
        struct IndexType
        {
            size_t index = 0;
            IndexType(size_t _idx) {
                index = _idx;
            };
        };

        void InitLayout();

        bool IsChunksFull() { return m_Chunks.size() * m_ChunkCapacity <= m_StoredEntityCount; }

        size_t AllocFreeBuffer();

        template<typename T, typename... Args>
        void CtorOnChunkImpl(size_t indexInChunk, Args... args);

        template<typename T>
        void DispatchCtor(size_t indexInChunk, size_t entityIdx);

        template<typename T>
        inline void InitImpl();

        template<typename T1, typename T2, typename... TC>
        inline void InitImpl();

    private:
        Vector<Chunk*> m_Chunks;

        size_t m_ChunkCapacity{ 0 };
        size_t m_StoredEntityCount{ 0 };

        Map<CmptType, size_t> m_TypeOffsetMap;
        CmptTypeSet m_CmptTypeSet;
    };
}

#include "Details/ArcheType.inl"