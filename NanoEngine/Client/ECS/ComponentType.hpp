#pragma once
#include "Common/Type/TypeDef.hpp"
#include "Common/Type/MapWrapper.hpp"
#include "Common/Type/ArrayWrapper.hpp"
#include "Common/Type/TypeInfo.hpp"
#include <functional>

namespace Nano
{
    class ComponentType
    {
    public:
        constexpr ComponentType(size_t hash) : m_Hash(hash) {};
        template<typename T>
        static constexpr ComponentType Of() { return ComponentType{TypeHash<T>}; }

        constexpr bool operator< (const ComponentType& rhs) const noexcept { return m_Hash < rhs.m_Hash; }
        constexpr bool operator<=(const ComponentType& rhs) const noexcept { return m_Hash <= rhs.m_Hash; }
        constexpr bool operator> (const ComponentType& rhs) const noexcept { return m_Hash > rhs.m_Hash; }
        constexpr bool operator>=(const ComponentType& rhs) const noexcept { return m_Hash >= rhs.m_Hash; }
        constexpr bool operator==(const ComponentType& rhs) const noexcept { return m_Hash == rhs.m_Hash; }
        constexpr bool operator!=(const ComponentType& rhs) const noexcept { return m_Hash != rhs.m_Hash; }
    private:
        size_t m_Hash;
    };

    class ComponentTypeSet
    {
        friend class ArcheType;
    public:
        inline void Insert(Span<const ComponentType> types)
        {
            for (const auto& item : types)
            {
                m_Data.insert(item);
            }
        }

        inline void Delete(Span<ComponentType> types)
        {
            for (const auto& item : types)
            {
                m_Data.erase(item);
            }
        }

        inline bool Contains(const ComponentType& type)
        {
            return m_Data.contains(type);
        }

        inline size_t Size() const { return m_Data.size(); }

        void Foreach(std::function<void(const ComponentType&)> func)
        {
            std::for_each(m_Data.begin(), m_Data.end(), func);
        }

        bool operator==(const ComponentTypeSet& rhs) const noexcept { return m_Data == rhs.m_Data; }
    private:
        Set<ComponentType> m_Data;
    };
}