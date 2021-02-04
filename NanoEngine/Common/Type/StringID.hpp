#pragma once
#include "Common/Fwd.hpp"
#include "Common/Type/MapWrapper.hpp"
#include "Common/Type/StringWrapper.hpp"
#include "Common/Type/TypeInfo.hpp"

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
        StringID(size_t hash) : m_Hash(hash) {};
        StringID(String str) : m_Hash(StringIDHelper::GetStrHash(str)) {}
        
        size_t GetHash() { return m_Hash; }

        StringID& operator=(const StringID& rhs) { m_Hash = rhs.m_Hash; return *this; }
        bool operator>(const StringID& rhs) { return m_Hash > rhs.m_Hash; }
        bool operator<(const StringID& rhs) { return m_Hash < rhs.m_Hash; }
        bool operator<=(const StringID& rhs) { return m_Hash <= rhs.m_Hash; }
        bool operator>=(const StringID& rhs) { return m_Hash >= rhs.m_Hash; }
        bool operator==(const StringID& rhs) { return m_Hash == rhs.m_Hash; }

    private:
        size_t m_Hash{ 0 };
    };
}