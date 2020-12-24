using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ClangSharp.Interop;

namespace AutoGenerator
{
    class MetaGenerator
    {
        unsafe public void Parse(string filePath)
        {
            CXIndex index = (CXIndex)clang.createIndex(0, 0);

            string[] cmdArds = { "x", "c++", "-std=c++17", "-D_ATTRIBUTE_", "-IC:/Code/NanoEngine" };
            ReadOnlySpan<string> cmdArgsPtr = new ReadOnlySpan<string>(cmdArds);
            CXTranslationUnit unit = CXTranslationUnit.CreateFromSourceFile(index, filePath, cmdArgsPtr, null);

            if (unit == null)
            {
                return;
            }

            CXCursor cursor = clang.getTranslationUnitCursor(unit);
            cursor.VisitChildren((CXCursor cursor, CXCursor parent, void* clientData) =>
            {
                if (ConcernedType(cursor.kind))
                {
                    CXString spelling = cursor.Spelling;
                    CXString kindSpelling = cursor.KindSpelling;
                    Console.WriteLine($"name:{spelling} kind:{kindSpelling} namespace:{NameSpaceSet.Instance.GetNameSpace(ref cursor)}");
                    NodeSet.Instance.AddCursor(cursor);
                }
                if (cursor.kind == CXCursorKind.CXCursor_LastPreprocessing)
                    return CXChildVisitResult.CXChildVisit_Break;
                else
                    return CXChildVisitResult.CXChildVisit_Recurse;
            }, new CXClientData());

            clang.disposeTranslationUnit(unit);
            clang.disposeIndex(index);
        }

        private bool ConcernedType(CXCursorKind kind)
        {
            switch (kind)
            {
                case CXCursorKind.CXCursor_ClassDecl:
                case CXCursorKind.CXCursor_StructDecl:
                case CXCursorKind.CXCursor_EnumDecl:
                case CXCursorKind.CXCursor_FunctionDecl:
                //case CXCursorKind.CXCursor_Namespace:
                //case CXCursorKind.CXCursor_VarDecl:
                case CXCursorKind.CXCursor_FunctionTemplate:
                //case CXCursorKind.CXCursor_CXXMethod:
                //case CXCursorKind.CXCursor_Constructor:
                //case CXCursorKind.CXCursor_ParmDecl:
                case CXCursorKind.CXCursor_TemplateTypeParameter:
                case CXCursorKind.CXCursor_NonTypeTemplateParameter:
                case CXCursorKind.CXCursor_TemplateTemplateParameter:
                case CXCursorKind.CXCursor_ClassTemplate:
                case CXCursorKind.CXCursor_TypeAliasDecl:
                    //case CXCursorKind.CXCursor_TypedefDecl:
                    //case CXCursorKind.CXCursor_AnnotateAttr:
                    return true;
                default:
                    return false;
            }
        }
    }
}
