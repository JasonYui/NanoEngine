#include "gtest/gtest.h"
#include <iostream>
#include "NanoEngine/Client/ECS/ArcheType.hpp"
#include "NanoEngine/Client/ECS/ArcheTypeManager.hpp"
#include "NanoEngine/Client/ECS/EntityManager.hpp"

using namespace Nano;

namespace Test
{
    class A  //size = 8
    {
        double i = 0;
    };

    class B  //size = 4
    {
        int i = 0;
    };

    class C  //size = 1
    {
        bool i = false;
    };

    TEST(ECSTest, Test_GetArcheType)
    {
        ArcheTypeManager manager;
        ArcheType* arche1 = manager.GetArcheType<A, B, C>();
        ArcheType* arche2 = manager.GetArcheType<A, C, B>();
        ArcheType* arche3 = manager.GetArcheType<A, C, C>();

        ASSERT_TRUE(arche1 == arche2);
        ASSERT_TRUE(arche3 != arche1);
    }

    TEST(ECSTest, Test_EntityCreateAndFree)
    {
        EntityManager entityManager;
        ArcheTypeManager* atm = new ArcheTypeManager();
        for (int i = 0; i < 10; ++i)
        {
            Entity e = entityManager.CreateEntity<A, B, C>(atm);
            std::cout << e.GetIndex() << e.GetVersion() << std::endl;
            entityManager.FreeEntity(e);
        }

        delete atm;
    }
}