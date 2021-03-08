#include "premake/meta_generator.hpp"

using namespace Nano::Premake;

int main()
{
    //MetaGenerator metaGen = MetaGenerator();
    //metaGen.Parse("C:/Code/NanoEngine/NanoEngine/Premake/Test.hpp");
    Parse("C:/Code/NanoEngine/NanoEngine/Common/Reflection/ReflectionTest.hpp");
    return 0;
}