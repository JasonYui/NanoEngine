#include "gtest/gtest.h"
#include "NanoEngine/Client/ECS/ArcheType.hpp"

using namespace Nano;

namespace Test
{
    class A
    {

    };

    class B
    {

    };

    class C
    {

    };

    TEST(ECSTest, Test_ArcheType)
    {
        ArcheType archeType;
        archeType.Init<A, B, C>();
    }
}