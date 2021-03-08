#pragma once
#include <vector>
#include <string>

namespace Nano::Premake
{
    enum class AccessModifier
    {
        _PUBLIC,
        _PROTECTED,
        _PRIVATE
    };

    struct Attr
    {
        std::string nameSpace;
        std::string name;
        std::string value;
    };

    struct FieldInfo
    {
        enum class Type {
            _VARIABLE,
            _FUNCTION,
            _VALUE // enum, static constepxr
        };
        Type type{ Type::_VARIABLE };
        AccessModifier access{ AccessModifier::_PUBLIC };
        std::vector<Attr> attrs;
        //std::vector<DeclSpecifier> declSpecifiers;
        std::vector<std::string> pointerOperators; // *, &, &&
        std::string name;
        std::vector<std::string> qualifiers; // const, volatile, &, &&
    };

    struct MethonInfo
    {
        AccessModifier access{ AccessModifier::_PUBLIC };
        std::vector<Attr> attrs;
        //std::vector<DeclSpecifier> declSpecifiers;
        std::vector<std::string> pointerOperators; // *, &, &&
        std::string name;
        std::string initializer; // expression or {expression}
        //std::vector<Parameter> parameters;
        std::vector<std::string> qualifiers; // const, volatile, &, &&
        bool isTemplate{ false };
    };

    struct MetaInfo
    {
        enum class Type
        {
            _CLASS,
            _STRUCT,
            _ENUM
        };

        Type type = Type::_CLASS;
        std::vector<std::string> nameSpace;
        std::vector<FieldInfo> fields;
    };
}