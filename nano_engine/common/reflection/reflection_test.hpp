#pragma once
#include "common/type/type_def.hpp"

using namespace Nano;

namespace Nano
{
    namespace Test
    {
        void Fuck(int a)
        {
            a++;
        }

        struct ATTRIBUTE(reflection) Point
        {
        public:
            ATTRIBUTE(xxx|a = b)
            ATTRIBUTE(c)
            const float x = 0.5f;
        private:
            float y = 1;

            const int Sum(int a, int b = 1) { return a + b; }
        };
    }
}
