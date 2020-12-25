using System;
using System.Collections.Generic;
using System.Linq;
using Mono.Options;

namespace AOTCompiler
{
    class Program
    {
        static void Main(string[] args)
        {
            AOTCmdArds cmdArgs = new AOTCmdArds();
            bool needHelp = false;

            var options = new OptionSet()
            {
                { "target=", "Target platform [Native|Interpreter]", v => cmdArgs.compilerTarget = Enum.TryParse<CompilerTarget>(v, true, out var t) ? t : CompilerTarget.Default },
                 { "h|help", "Print this help", _ => needHelp = true },
            };

            List<string> extra = options.Parse(args);
            if (needHelp || (extra.Count < 2))
            {
                Console.Out.WriteLine("usage: il2c.exe [options] <output_path> <assembly_path>");
                options.WriteOptionDescriptions(Console.Out);
            }
            else
            {
                string outputPath = extra[0];
                IEnumerable<string> assemblyPaths = extra.Skip(1);

                /*Dispatcher.TranslateAll(
                    Console.Out,
                    outputPath,
                    cmdArgs,
                    assemblyPaths
                );*/
            }
        }
    }
}
