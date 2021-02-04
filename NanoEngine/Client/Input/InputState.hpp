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
        BaseInputType m_InputType{ BaseInputType::_None };
        BaseInputType m_PrevInputType{ BaseInputType::_None };
    };

}