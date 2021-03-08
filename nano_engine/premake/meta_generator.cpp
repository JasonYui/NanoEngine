#include "premake/meta_generator.hpp"
#include <iostream>
#include <functional>

#ifdef _ATTRIBUTE_
#define PROPERTY(...) __attribute__((annotate(#__VA_ARGS__)))
#else
#define PROPERTY(...)
#endif

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

        std::function<void(const char*)> processNameSpace = [this](const char* nameSpace)
        {
            while (m_NameSpace.size() > 0)
            {
                if (nameSpace != m_NameSpace.back())
                    m_NameSpace.pop_back();
                else
                    break;
            }
            if (m_NameSpace.size() == 0)
                m_NameSpace.push_back(nameSpace);
        };

        if (clang_getCursorKind(cursor) == CXCursorKind::CXCursor_NamespaceRef)
        {
            processNameSpace(GetFromCXString(cursorSpelling));
        }
        else if (clang_getCursorKind(cursor) == CXCursorKind::CXCursor_ClassDecl || clang_getCursorKind(cursor) == CXCursorKind::CXCursor_StructDecl)
        {
            
        }
        else if (clang_getCursorKind(parent) == CXCursorKind::CXCursor_NamespaceRef)
        {

            auto parentNameSpace = GetFromCXString(clang_getCursorSpelling(parent));
            processNameSpace(parentNameSpace);
        }
        else
        {
            m_StoredCursorInfos.push_back({cursor, parent, clientData});
        }
    }

    void MetaGenerator::GenMetaInfo()
    {
        if (m_StoredCursorInfos.size() <= 0)
            return;
        
        CursorInfo front = m_StoredCursorInfos.front();
        if (clang_getCursorKind(front.cursor) != CXCursorKind::CXCursor_ClassDecl && 
            clang_getCursorKind(front.cursor) != CXCursorKind::CXCursor_StructDecl &&
            clang_getCursorKind(front.cursor) != CXCursorKind::CXCursor_EnumDecl)
        {
            std::cerr << "[MetaGenerator::GenMetaInfo] invalid cursor kind" << std::endl;
            return;
        }

        MetaInfo meta;
        meta.nameSpace = m_NameSpace;

        for (auto iter = m_StoredCursorInfos.begin()++; iter != m_StoredCursorInfos.end(); iter++)
        {

        }

        m_StoredCursorInfos.clear();
    }

    struct CursorInfo
    {
        CXCursor cursor;
        CXCursor parent;
        CXClientData clientData;
    };

    std::vector<CursorInfo> m_StoredCursorInfos;
    std::vector<std::string> m_NameSpace;

    void GenMetaInfo();

    const char* GetFromCXString(const CXString& cxStr)
    {
        auto ret = clang_getCString(cxStr);
        clang_disposeString(cxStr);
        return ret;
    }

    CXChildVisitResult TranslationUnitVisitor(CXCursor cursor, CXCursor parent, CXClientData clientData)
    {
        CXString cursorSpelling = clang_getCursorSpelling(cursor);
        CXString kindSpelling = clang_getCursorKindSpelling(clang_getCursorKind(cursor));
        std::cout << "cursor: " << GetFromCXString(cursorSpelling) << " kind: " << GetFromCXString(kindSpelling) << std::endl;

        std::function<void(const char*)> processNameSpace = [](const char* nameSpace)
        {
            while (m_NameSpace.size() > 0)
            {
                if (nameSpace != m_NameSpace.back())
                    m_NameSpace.pop_back();
                else
                    break;
            }
            if (m_NameSpace.size() == 0)
                m_NameSpace.push_back(nameSpace);
        };

        if (clang_getCursorKind(parent) == CXCursorKind::CXCursor_Namespace)
        {
            auto parentNameSpace = GetFromCXString(clang_getCursorSpelling(parent));
            processNameSpace(parentNameSpace);
            GenMetaInfo();
        }

        if (clang_getCursorKind(cursor) == CXCursorKind::CXCursor_Namespace)
        {
            m_NameSpace.push_back(GetFromCXString(clang_getCursorSpelling(cursor)));
        }
        else
        {
            m_StoredCursorInfos.push_back({ cursor, parent, clientData });
        }

        return CXChildVisit_Recurse;
    }

    void Parse(const char* fileName)
    {
        m_StoredCursorInfos.clear();
        m_NameSpace.clear();
        CXIndex index = clang_createIndex(0, 0);
        CXTranslationUnit unit;

        std::vector<std::string> arguments;
        arguments.push_back("-x");
        arguments.push_back("c++");
        arguments.push_back("-std=c++17");
        arguments.push_back("-D_ATTRIBUTE_");
        //arguments.push_back("-ID:/usr/include/");
        //arguments.push_back("-I../include/");
        std::vector<const char*> cstrArguments;

        for (const auto& i : arguments)
        {
            cstrArguments.push_back(i.c_str());
        }

        CXErrorCode error = clang_parseTranslationUnit2(index, fileName, cstrArguments.data(), cstrArguments.size(), nullptr, 0,
            CXTranslationUnit_None, &unit);

        if (error != CXErrorCode::CXError_Success)
        {
            std::cerr << "parse " << fileName << " failed, error code: " << error << std::endl;
        }

        CXCursor cursor = clang_getTranslationUnitCursor(unit);

        clang_visitChildren(
            cursor,
            &TranslationUnitVisitor,
            nullptr
        );

        clang_disposeTranslationUnit(unit);
        clang_disposeIndex(index);
    }

    void GenMetaInfo()
    {
        if (m_StoredCursorInfos.size() <= 0)
            return;

        CursorInfo front = m_StoredCursorInfos.front();
        if (clang_getCursorKind(front.cursor) != CXCursorKind::CXCursor_ClassDecl &&
            clang_getCursorKind(front.cursor) != CXCursorKind::CXCursor_StructDecl &&
            clang_getCursorKind(front.cursor) != CXCursorKind::CXCursor_EnumDecl)
        {
            std::cerr << "[MetaGenerator::GenMetaInfo] invalid cursor kind" << std::endl;
            return;
        }

        MetaInfo meta;
        meta.nameSpace = m_NameSpace;

        for (auto iter = m_StoredCursorInfos.begin() + 1; iter != m_StoredCursorInfos.end(); iter++)
        {
            if (clang_getCursorKind(iter->cursor) == CXCursorKind::CXCursor_FieldDecl)
            {
                auto name = GetFromCXString(clang_getCursorSpelling(iter->cursor));
                FieldInfo field{ FieldInfo::Type::_VARIABLE, AccessModifier::_PUBLIC };
            }
        }

        m_StoredCursorInfos.clear();
    }
}