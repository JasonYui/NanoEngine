#include "gtest/gtest.h"
#include "common/math/vector.hpp"
#include "common/math/quaternion.hpp"

using namespace Nano;

namespace Test
{
    TEST(MathTest, Test_Vector)
    {
        Vector3f vec3(1.0f, 2.0f, 3.0f);
        Vector3f newVec3 = vec3 * 2.0f;

        Vector3f result = vec3.Cross(newVec3);
    }

    TEST(MathTest, Test_Quaternion)
    {
        Vector3f vec3(1.0f, 2.0f, 3.0f);
        Quaternionf q(vec3);
    }
}