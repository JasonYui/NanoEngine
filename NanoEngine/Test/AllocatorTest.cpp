#include "gtest/gtest.h"
#include "NanoEngine/Common/Memory/Allocator.hpp"

using namespace Nano;
TEST(AllocatorTest, Test_OperatorNew) 
{
    Allocator alloc = Allocator(4, 4 * 12, 4);
    void*p = alloc.Allocate();
    alloc.Free(p);
}