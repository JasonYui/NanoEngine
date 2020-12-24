using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AutoGenerator
{
    class TypeInfoGenerator
    {
        public void Generate()
        {
            string attr = "refl";
            foreach(Node node in NodeSet.Instance)
            {
                if (node.TryGetAttributeValue(ref attr, out string value))
                {

                }
            }
        }
    }
}
