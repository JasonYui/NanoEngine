#pragma once

#include "common/fwd.hpp"
#include "common/type/map_wrapper.hpp"
#include "common/type/string_wrapper.hpp"
#include "common/type/type_info.hpp"

namespace Nano
{
    class StringIDHelper
    {
        friend class StringID;
        using Hash = size_t;
        static Hash GetStrHash(const String& str)
        {
            auto iter = m_StrToHashMap.find(str);
            if (iter != m_StrToHashMap.end())
                return iter->second;

            return StrHashGenerator::Gen(str);
        }

        static HashMap<String, Hash> m_StrToHashMap;
    };


    class StringID
    {
    public:
        static const StringID Empty() { return StringID(0); }
    public:
        StringID(size_t hash) : m_Hash(hash) {};
        StringID(String str) : m_Hash(StringIDHelper::GetStrHash(str)) {}
        
        size_t GetHash() const { return m_Hash; }

        StringID& operator=(const StringID& rhs) { m_Hash = rhs.m_Hash; return *this; }
        bool operator>(const StringID& rhs) { return m_Hash > rhs.m_Hash; }
        bool operator<(const StringID& rhs) { return m_Hash < rhs.m_Hash; }
        bool operator<=(const StringID& rhs) { return m_Hash <= rhs.m_Hash; }
        bool operator>=(const StringID& rhs) { return m_Hash >= rhs.m_Hash; }

    private:
        size_t m_Hash{ 0 };
    };

    inline bool operator==(const StringID& lhs, const StringID& rhs) { return lhs.GetHash() == rhs.GetHash(); }
}

template <>
struct std::hash<Nano::StringID>
{
    std::size_t operator()(const Nano::StringID& strId) const
    {
        return strId.GetHash();
    }
};