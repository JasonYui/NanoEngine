using ClangSharp.Interop;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AutoGenerator
{
    class NameSpaceSet
    {
        static public NameSpaceSet Instance
        {
            get
            {
                if (g_Instance == null)
                {
                    lock(g_Mutex)
                    {
                        if (g_Instance == null)
                            g_Instance = new NameSpaceSet();
                    }
                }
                return g_Instance;
            }
        }

        struct NodeInfo
        {
            string name;
            CXCursorKind kind;
        }

        static private NameSpaceSet g_Instance;
        static private object g_Mutex = new object();
        private Dictionary<string, List<NodeInfo>> m_NameSpaceContainer = new Dictionary<string, List<NodeInfo>>();
        public string GetNameSpace(ref CXCursor cursor)
        {
            CXCursor parent = clang.getCursorSemanticParent(cursor);
            Stack<string> nameSpace = new Stack<string>();
            while (parent.kind != CXCursorKind.CXCursor_TranslationUnit && parent.kind != CXCursorKind.CXCursor_FirstDecl)
            {
                nameSpace.Push(parent.Spelling.ToString());
                parent = clang.getCursorSemanticParent(parent);
            }

            StringBuilder fullNameSpace = new StringBuilder();
            while (nameSpace.Count > 0)
            {
                fullNameSpace.Append($"{nameSpace.Pop()}::");
            }
            return fullNameSpace.ToString();
        }
    }
}
