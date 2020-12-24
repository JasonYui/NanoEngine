using System;

namespace AutoGenerator
{
    class Program
    {
        unsafe static void Main(string[] args)
        {
            MetaGenerator metaGen = new MetaGenerator();
            metaGen.Parse("C:/Code/NanoEngine/NanoEngine/Common/Reflection/ReflectionTest.hpp");
        }
    }
}
