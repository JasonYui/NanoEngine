#include "gtest/gtest.h"
#include <iostream>
#include "Client/ECS/ArcheType.hpp"
#include "Client/ECS/EntityManager.hpp"

using namespace Nano;

namespace Test
{
    struct A  //size = 8
    {
        double i = 0;
    };

    struct B  //size = 4
    {
        int i = 0;
    };

    struct C  //size = 1
    {
        bool i = false;
    };

    struct D
    {
        D() = default;
        D(bool _i) : i(_i) {};
        bool i = false;
        int j = 2;
        int k = -1;
    };

    TEST(ECSTest, Test_EntityCreateAndFree)
    {
        EntityManager entityManager;
        Entity e0 = entityManager.CreateEntity<A, B, C>();
        Entity e1 = entityManager.CreateEntity<B, C, A>();
        Entity e2 = entityManager.CreateEntity<B, C>();

        EXPECT_TRUE(entityManager.IsSameArcheType(e0, e1));
        EXPECT_TRUE(!entityManager.IsSameArcheType(e0, e2));

        entityManager.FreeEntity(e0);
        entityManager.FreeEntity(e1);
        entityManager.FreeEntity(e2);
    }

    TEST(ECSTest, Test_GetComponent)
    {
        EntityManager entityManager;
        Entity e0 = entityManager.CreateEntity<A, B, D>();

        D* cmpt = entityManager.GetComponent<D>(e0);
        D* defaultCmpt = new D();
        EXPECT_EQ(cmpt->i, defaultCmpt->i);
        EXPECT_EQ(cmpt->j, defaultCmpt->j);
        EXPECT_EQ(cmpt->k, defaultCmpt->k);
        delete defaultCmpt;
    }

    TEST(ECSTest, Test_EntityAttach)
    {
        EntityManager entityManager;
        Entity e0 = entityManager.CreateEntity<A, B>();
        Entity e1 = entityManager.CreateEntity<A, B>();
        Entity e2 = entityManager.CreateEntity<A, B, D>();

        entityManager.Attach<D, bool>(e0, true);
        EXPECT_FALSE(entityManager.IsSameArcheType(e0, e1));
        EXPECT_TRUE(entityManager.IsSameArcheType(e0, e2));
    }

    TEST(ECSTest, Test_EntityDetach)
    {
        EntityManager entityManager;
        Entity e0 = entityManager.CreateEntity<A, B, D>();
        Entity e1 = entityManager.CreateEntity<A, B, D>();
        Entity e2 = entityManager.CreateEntity<B, D>();

        D* oldCmpt = entityManager.GetComponent<D>(e0);

        entityManager.Detach<A>(e0);
        D* newCmpt = entityManager.GetComponent<D>(e0);
        EXPECT_EQ(newCmpt->i, false);
        EXPECT_EQ(newCmpt->j, 2);
        EXPECT_EQ(newCmpt->k, -1);
        EXPECT_FALSE(entityManager.IsSameArcheType(e0, e1));
        EXPECT_TRUE(entityManager.IsSameArcheType(e0, e2));
    }

    TEST(ECSTest, Test_Foreach)
    {
        EntityManager entityManager;
        Entity e0 = entityManager.CreateEntity<A, B, D>();
        Entity e1 = entityManager.CreateEntity<B, D>();
        Entity e2 = entityManager.CreateEntity<A, C, B, D>();

        entityManager.Foreach<B, D>([](Entity e, B* bc, D* dc) {
            EXPECT_EQ(dc->i, false);
            EXPECT_EQ(dc->j, 2);
            EXPECT_EQ(dc->k, -1);
        });
    }
}