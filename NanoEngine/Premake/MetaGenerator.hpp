#pragma once
#include <clang-c/Index.h>
#include <stack>

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
        std::stack<CursorInfo> m_StoredCursorInfos;
    };
}