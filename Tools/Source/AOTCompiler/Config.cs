using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AOTCompiler
{
    public struct AOTCmdArds
    {
        public CompilerTarget compilerTarget;
    }

    public enum CompilerTarget : Int16
    {
        Native = 0,
        Interpreter = 1,
        Default = Native
    }
}
