#include "gtest/gtest.h"
#include "NanoEngine/Common/Memory/Allocator.hpp"

using namespace Nano;
TEST(AllocatorTest, test1) 
{
    Allocator alloc = Allocator();
    void*p = alloc.Allocate();
    alloc.Free(p);
}