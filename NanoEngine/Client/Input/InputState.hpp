#pragma once

#include "Common/Math/Vector.hpp"

#include "InputEnum.hpp"

namespace Nano
{
    struct InputState
    {
        RawInputType inputType{ RawInputType::_None };
        RawInputType prevInputType{ RawInputType::_None };
        float holdTime = 0.0f;
    };
}