namespace Nano
{
    template<typename... TC>
    void ArcheType::Init()
    {
        InitImpl<IndexType, TC...>();
        InitLayout();
    }

    template<typename... TC>
    bool ArcheType::IsSame() const
    {
        static_assert((!std::is_same_v<IndexType, TC> && ...));
        if (sizeof...(TC) == GetComponentCount())
        {
            if ((m_CmptTypeSet.contains(CmptType::Of<TC>()) && ...))
            {
                return true;
            }
        }

        return false;
    }

    template<typename... TC>
    bool ArcheType::ContainsAll() const
    {
        if ((m_CmptTypeSet.contains(CmptType::Of<TC>()) && ...))
        {
            return true;
        }
        return false;
    }

    template<typename T, typename... Args>
    void ArcheType::CtorOnChunkImpl(size_t indexInChunk, Args... args)
    {
        size_t indexInFreeChunk = indexInChunk % m_ChunkCapacity;
        Chunk* freeChunk = m_Chunks.back();
        assert(freeChunk != nullptr);

        auto result = m_TypeOffsetMap.find(CmptType::Of<T>());
        if (result != m_TypeOffsetMap.end())
        {
            ubyte* data = freeChunk->Data() + result->second + indexInFreeChunk * sizeof(T);
            new(data)T(args...);
        }
    }

    template<typename T>
    void ArcheType::DispatchCtor(size_t indexInChunk, size_t entityIdx)
    {
        if constexpr (std::is_same_v<T, IndexType>)
            CtorOnChunkImpl<T, size_t>(indexInChunk, entityIdx);
        else
            CtorOnChunkImpl<T>(indexInChunk);
    }

    template<typename... TC>
    bool ArcheType::IsCmptTypeValid() const
    {
        return ((m_CmptTypeSet.contains(CmptType::Of<TC>()) && !std::is_same_v<TC, IndexType>) && ...);
    }

    template<typename T1, typename T2, typename... TC>
    size_t ArcheType::Ctor(size_t entityIdx)
    {
        size_t idxInArcheType = AllocFreeBuffer();
        DispatchCtor<IndexType>(idxInArcheType, entityIdx);
        DefaultCtorOnChunk<T1, T2, TC...>(idxInArcheType);
        return idxInArcheType;
    }

    template<typename T1, typename T2, typename... TC>
    void ArcheType::DefaultCtorOnChunk(size_t indexInChunk)
    {
        CtorOnChunkImpl<T1>(indexInChunk);
        CtorOnChunkImpl<T2>(indexInChunk);
        (CtorOnChunkImpl<TC>(indexInChunk), ...);
    }

    template<typename T, typename... Args>
    void ArcheType::CustomCtorOnChunk(size_t indexInChunk, Args&&... args)
    {
        CtorOnChunkImpl<T, Args...>(indexInChunk, args...);
    }

    template<typename T>
    void ArcheType::DtorOnChunk(size_t idxInArcheType)
    {
        if (!IsCmptTypeValid<T>())
            throw std::invalid_argument("[ArcheType::DtorOnChunk] component type is invalid");

        T* instance = GetComponent<T>(idxInArcheType);
        instance->~T();
    }

    template<typename T1, typename T2, typename... TC>
    void ArcheType::DtorOnChunk(size_t idxInArcheType)
    {
        DtorOnChunk<T1>(idxInArcheType);
        DtorOnChunk<T2, TC...>(idxInArcheType);
    }

    template<typename T>
    T* ArcheType::GetComponent(size_t idxInArcheType)
    {
        assert(idxInArcheType < m_StoredEntityCount);

        CmptType cmptType = CmptType::Of<T>();
        auto iter = m_TypeOffsetMap.find(cmptType);
        if (iter != m_TypeOffsetMap.end())
        {
            size_t chunkIdx = idxInArcheType / m_ChunkCapacity;
            size_t idxInChunk = idxInArcheType % m_ChunkCapacity;
            assert(chunkIdx < m_Chunks.size());
            ubyte* locateBuffer = m_Chunks[chunkIdx]->Data();
            return reinterpret_cast<T*>(locateBuffer + iter->second + idxInChunk * cmptType.GetSize());
        }
        return nullptr;
    }

    template<typename T>
    void ArcheType::InitImpl()
    {
        CmptType cmptType = CmptType::Of<T>();
        assert(m_CmptTypeSet.contains(cmptType) == false);

        m_CmptTypeSet.insert(std::move(cmptType));
    }

    template<typename T1, typename T2, typename... TC>
    void ArcheType::InitImpl()
    {
        InitImpl<T1>();
        InitImpl<T2, TC...>();
    }
}