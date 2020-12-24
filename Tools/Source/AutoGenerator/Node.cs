using ClangSharp.Interop;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AutoGenerator
{
    abstract class Node
    {
        public CXCursor Cursor { get; private set; }
        public string NameSpace { get; private set; }
        public CX_CXXAccessSpecifier AccessSpecifier { get; private set; }
        protected Dictionary<string, string> m_AttributeMap = new Dictionary<string, string>();

        public unsafe Node(ref CXCursor cursor)
        {
            Cursor = cursor;
            NameSpace = NameSpaceSet.Instance.GetNameSpace(ref cursor);
            AccessSpecifier = clang.getCXXAccessSpecifier(cursor);
            cursor.VisitChildren((CXCursor cursor, CXCursor parent, void* clientData) =>
            {
                if (cursor.kind == CXCursorKind.CXCursor_AnnotateAttr)
                {
                    string content = cursor.Spelling.ToString();
                    string[] splitArray = content.Split("|");
                    foreach(string item in splitArray)
                    {
                        string[] subSplitArray = item.Split("=");
                        if (subSplitArray.Length == 1)
                            m_AttributeMap.Add(item.Trim(), string.Empty);
                        else if (subSplitArray.Length == 1)
                            m_AttributeMap.Add(subSplitArray[0].Trim(), subSplitArray[1].Trim());
                        //else
                            //warning
                    }
                }

                ProcessChild(ref cursor);
                return CXChildVisitResult.CXChildVisit_Continue;
            }, new CXClientData());
        }

        public string GetName() => Cursor.Spelling.ToString();
        public string GetFullName() => NameSpace + GetName();

        public abstract string ToJson();
        protected virtual void ProcessChild(ref CXCursor cursor) { }
        public virtual bool TryGetAttributeValue(ref string attr, out string value) => m_AttributeMap.TryGetValue(attr, out value);
    }

    class VarNode : Node
    {
        public VarNode(ref CXCursor cursor) : base(ref cursor)
        {
            
        }

        public override string ToJson()
        {
            throw new NotImplementedException();
        }
    }

    class FieldNode : Node
    {
        public string DefaultValue { get; private set; }
        public bool IsConst { get => Type.IsConstQualified; }
        public CXType Type { get; private set; }
        public FieldNode(ref CXCursor cursor) : base(ref cursor)
        {
            Type = clang.getCursorType(cursor);
        }

        public void GetValue()
        {
        }

        public override string ToJson()
        {
            return string.Empty;
        }
    }

    class MethodNode : Node
    {
        private List<VarNode> m_Params = new List<VarNode>();
        public MethodNode(ref CXCursor cursor) : base(ref cursor)
        {

        }

        public override string ToJson()
        {
            throw new NotImplementedException();
        }

        protected override void ProcessChild(ref CXCursor cursor)
        {
            if (cursor.kind == CXCursorKind.CXCursor_ParmDecl)
            {
                m_Params.Add(new VarNode(ref cursor));
            }
        }
    }

    class ClassNode : Node
    {
        List<FieldNode> m_Fields = new List<FieldNode>();
        List<MethodNode> m_Methods = new List<MethodNode>();

        public unsafe ClassNode(ref CXCursor cursor) : base(ref cursor)
        {
        }

        public override string ToJson()
        {
            return string.Empty;
        }

        protected override void ProcessChild(ref CXCursor cursor)
        {
            if (cursor.kind == CXCursorKind.CXCursor_FieldDecl)
            {
                m_Fields.Add(new FieldNode(ref cursor));
            }
            else if (cursor.kind == CXCursorKind.CXCursor_CXXMethod)
            {
                m_Methods.Add(new MethodNode(ref cursor));
            }
        }

        public override bool TryGetAttributeValue(ref string attr, out string value)
        {
            if (m_AttributeMap.TryGetValue(attr, out value))
                return true;

            foreach (var field in m_Fields)
            {
                if (field.TryGetAttributeValue(ref attr, out value))
                    return true;
            }

            foreach (var method in m_Methods)
            {
                if (method.TryGetAttributeValue(ref attr, out value))
                    return true;
            }

            return false;
        }
    }
}
