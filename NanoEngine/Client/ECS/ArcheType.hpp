#pragma once
#include "NanoEngine/Common/Type/TypeDef.hpp"

namespace Nano
{
    class ArcheType
    {
        friend class ArcheTypeManager;
    public:
        template<typename... TC>
        void Init();

        template<typename T>
        int GetComponentIndex();
    private:
        template<typename T>
        void InitImpl();

        template<typename T1, typename T2, typename... TC>
        void InitImpl();
        

        int32_t m_ComponentCount{ 0 };
        size_t* m_TypeHashes;
        size_t m_ComponentTotalSize{ 0 };
    };

    template<typename... TC>
    void ArcheType::Init()
    {
        m_TypeHashes = new size_t[sizeof...(TC)]();
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
            //SizeOfs[i + 1] = SizeOfs[i];
        }
        m_TypeHashes[i + 1] = hash;
        //SizeOfs[i + 1] = sizeof(T);

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