#include "gtest/gtest.h"
#include "NanoEngine/Common/Memory/Allocator.hpp"

using namespace Nano;

namespace Test
{
    TEST(AllocatorTest, Test_Allocate) 
    {
        Allocator alloc = Allocator(4, 32, 4);
        for (size_t i = 0; i < 20; ++i)
        {
            void*p = alloc.Allocate();
            alloc.Free(p);
        }
    }

    class Test_Class
    {
        int32_t m_Index{ 0 };
    public:
        void* operator new(size_t size)
        {
            Allocator alloc = Allocator(4, 32, 4);
            void* p = alloc.Allocate();
            return p;
        }
    };

    TEST(AllocatorTest, Test_OperatorNew)
    {
        Test_Class* alloc = new Test_Class();
    }
}