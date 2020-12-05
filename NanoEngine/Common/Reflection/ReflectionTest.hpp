#pragma once
#include "NanoEngine/Common/Reflection/Reflection.hpp"

using namespace Ubpa::USRefl;

struct Point
{
    float x;
    float y;

    float Sum() { return x + y; }
};
