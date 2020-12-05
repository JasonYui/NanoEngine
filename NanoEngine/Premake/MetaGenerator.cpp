#include "NanoEngine/Premake/MetaGenerator.hpp"
#include <iostream>
#include <functional>

namespace Nano::Premake
{
    void MetaGenerator::Parse(const char* fileName)
    {
        CXIndex index = clang_createIndex(0, 0);
        CXTranslationUnit unit;
        CXErrorCode error = clang_parseTranslationUnit2(index, fileName, nullptr, 0, nullptr, 0, 
            CXTranslationUnit_None, &unit);

        if (error != CXErrorCode::CXError_Success)
        {
            std::cerr<< "parse " << fileName << " failed, error code: " << error <<std::endl; 
        }

        CXCursor cursor = clang_getTranslationUnitCursor(unit);

        clang_visitChildren(
            cursor,
            [](CXCursor c, CXCursor parent, CXClientData clientData)
            {
                CXString cursorSpelling = clang_getCursorSpelling(c);
                CXString kindSpelling = clang_getCursorKindSpelling(clang_getCursorKind(c));
                std::cout<< "cursor: " << GetFromCXString(cursorSpelling) << " kind: " << GetFromCXString(kindSpelling) << std::endl;
                return CXChildVisit_Recurse;
            },
            nullptr
        );

        clang_disposeTranslationUnit(unit);
        clang_disposeIndex(index);
    }

    void MetaGenerator::ProcessCursorInfo(CXCursor cursor, CXCursor parent, CXClientData clientData)
    {
        CXString cursorSpelling = clang_getCursorSpelling(cursor);
        CXString kindSpelling = clang_getCursorKindSpelling(clang_getCursorKind(cursor));
        std::cout<< "cursor: " << GetFromCXString(cursorSpelling) << " kind: " << GetFromCXString(kindSpelling) << std::endl;
    }
}