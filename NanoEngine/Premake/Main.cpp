#include "NanoEngine/Premake/MetaGenerator.hpp"

using namespace Nano::Premake;

int main()
{
    MetaGenerator metaGen = MetaGenerator();
    metaGen.Parse("C:/Code/NanoEngine/NanoEngine/Premake/Test.hpp");
    return 0;
}