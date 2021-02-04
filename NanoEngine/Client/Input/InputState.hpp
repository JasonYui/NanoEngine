#pragma once
#include "InputEnum.hpp"

namespace Nano
{
    struct InputState
    {
        struct Button
        {
            union
            {
                bool boolValue;
                float floatValue;
            };
        };
        BaseInputType inputType{ BaseInputType::_None };
        BaseInputType prevInputType{ BaseInputType::_None };
        float holdTime = 0.0f;
    };

}