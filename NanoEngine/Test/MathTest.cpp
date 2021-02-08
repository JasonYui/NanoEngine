#include "gtest/gtest.h"
#include "Common/Math/Vector.hpp"
#include "Common/Math/Quaternion.hpp"

using namespace Nano;

namespace Test
{
    TEST(AllocatorTest, Test_Vector)
    {
        Vector3f vec3(1.0f, 2.0f, 3.0f);
        Vector3f newVec3 = vec3 * 2.0f;

        Vector3f result = vec3.Cross(newVec3);
    }

    TEST(AllocatorTest, Test_Quaternion)
    {
        Vector3f vec3(1.0f, 2.0f, 3.0f);
        Quaternionf q(vec3);
    }
}