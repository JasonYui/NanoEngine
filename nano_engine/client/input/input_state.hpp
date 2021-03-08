#pragma once

#include "common/math/vector.hpp"

#include "client/input/input_enum.hpp"

namespace Nano
{
    struct InputState
    {
        RawInputType inputType{ RawInputType::_None };
        RawInputType prevInputType{ RawInputType::_None };
        float holdTime = 0.0f;
    };
}