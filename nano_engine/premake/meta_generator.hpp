#pragma once
#include <clang-c/Index.h>
#include <stack>
#include <vector>
#include <string>
#include "premake/meta_info.hpp"

namespace Nano::Premake
{
    class MetaGenerator
    {
    public:
        void Parse(const char* fileName);

    private:
        static const char* GetFromCXString(const CXString& cxStr)
        {
            auto ret = clang_getCString(cxStr);
            clang_disposeString(cxStr);
            return ret;
        }

        struct CursorInfo
        {
            CXCursor cursor;
            CXCursor parent;
            CXClientData clientData;
        };
        

        void ProcessCursorInfo(CXCursor cursor, CXCursor parent, CXClientData clientData);
        void GenMetaInfo();

        std::string GetNameSpace()
        {
            std::string ret;
            for (auto&& sub : m_NameSpace)
            {
                if (ret.length() != 0)
                    ret += ("::" + sub);
                else
                    ret += sub;
            }

            return ret;
        }

        std::vector<CursorInfo> m_StoredCursorInfos;
        std::vector<std::string> m_NameSpace;
    };

    void Parse(const char* fileName);
}