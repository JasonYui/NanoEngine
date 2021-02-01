#pragma once
#include "Common/Fwd.hpp"
#include "Common/Type/MapWrapper.hpp"
#include "Common/Type/StringWrapper.hpp"
#include "Common/Type/TypeInfo.hpp"

namespace Nano
{
    class StringID
    {
    public:
        StringID(uint32_t hash) : m_Hash(hash) {};
        StringID(String str) : m_Hash(StringIDHelper::GetStrHash(str)) {}
        
        uint32_t GetHash() { return m_Hash; }

        StringID& operator=(const StringID& rhs) { m_Hash = rhs.m_Hash; return *this; }
        bool operator>(const StringID& rhs) { return m_Hash > rhs.m_Hash; }
        bool operator<(const StringID& rhs) { return m_Hash < rhs.m_Hash; }
        bool operator<=(const StringID& rhs) { return m_Hash <= rhs.m_Hash; }
        bool operator>=(const StringID& rhs) { return m_Hash >= rhs.m_Hash; }
        bool operator==(const StringID& rhs) { return m_Hash == rhs.m_Hash; }

    private:
        uint32_t m_Hash{ 0 };
    };

    class StringIDHelper
    {
        friend StringID;
        using Hash = uint32_t;
        static Hash GetStrHash(const String& str)
        {
            auto iter = m_StrToHashMap.find(str);
            if (iter != m_StrToHashMap.end())
                return iter->second;

            return StrHashGenerator::Gen(str);
        }

        static HashMap<String, Hash> m_StrToHashMap;
    };
}