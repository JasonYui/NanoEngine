#pragma once
#include "Common/Type/TypeDef.hpp"
#include "Common/Type/MapWrapper.hpp"
#include "Common/Type/ArrayWrapper.hpp"
#include "Common/Type/TypeInfo.hpp"
#include <functional>
#include <typeindex>

namespace Nano
{
    class CmptType
    {
    public:
        explicit CmptType() = default;
        explicit CmptType(size_t hash, size_t alignment, size_t size) : m_Hash(hash), m_Alignment(alignment), m_Size(size) {};
        explicit CmptType(const CmptType& cmptType) : m_Hash(cmptType.m_Hash), m_Alignment(cmptType.m_Alignment), m_Size(cmptType.m_Size) {};
        explicit CmptType(CmptType&& cmptType) noexcept : m_Hash(cmptType.m_Hash), m_Alignment(cmptType.m_Alignment), m_Size(cmptType.m_Size) {};
        template<typename T>
        static CmptType Of() { return CmptType{ typeid(T).hash_code(), alignof(T), sizeof(T) }; };

        size_t GetHash() const { return m_Hash; }
        size_t GetAlignment() const { return m_Alignment; }
        size_t GetSize() const { return m_Size; }

        template<typename T>
        bool IsType() const { return *this == CmptType::Of<T>(); }

        CmptType& operator= (const CmptType& rhs) = default;
        constexpr bool operator< (const CmptType& rhs) const noexcept { return m_Hash < rhs.m_Hash; }
        constexpr bool operator<=(const CmptType& rhs) const noexcept { return m_Hash <= rhs.m_Hash; }
        constexpr bool operator> (const CmptType& rhs) const noexcept { return m_Hash > rhs.m_Hash; }
        constexpr bool operator>=(const CmptType& rhs) const noexcept { return m_Hash >= rhs.m_Hash; }
        constexpr bool operator==(const CmptType& rhs) const noexcept { return m_Hash == rhs.m_Hash; }
        constexpr bool operator!=(const CmptType& rhs) const noexcept { return m_Hash != rhs.m_Hash; }
    private:
        size_t m_Hash{ 0 };
        size_t m_Alignment{ 0 };
        size_t m_Size{ 0 };
    };
}