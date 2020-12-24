using ClangSharp.Interop;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AutoGenerator
{
    class NodeSet : IEnumerable<Node>
    {
        private Dictionary<string, Node> m_NodeMap = new Dictionary<string, Node>();
        static public NodeSet Instance
        {
            get
            {
                if (g_Instance == null)
                {
                    lock (g_Mutex)
                    {
                        if (g_Instance == null)
                            g_Instance = new NodeSet();
                    }
                }
                return g_Instance;
            }
        }

        static private NodeSet g_Instance;
        static private object g_Mutex = new object();

        public void AddCursor(CXCursor cursor)
        {
            if (cursor.kind == CXCursorKind.CXCursor_ClassDecl || cursor.kind == CXCursorKind.CXCursor_StructDecl)
            {
                Node node = new ClassNode(ref cursor);
                m_NodeMap.Add(node.GetFullName(), node);
            }

        }

        public IEnumerator<Node> GetEnumerator()
        {
            foreach (var item in m_NodeMap)
            {
                yield return item.Value;
            }
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }
    }
}
