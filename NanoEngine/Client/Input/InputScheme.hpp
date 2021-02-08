#pragma once
#include "Common/Fwd.hpp"
#include "Common/Type/StringID.hpp"
#include "Common/Type/ArrayWrapper.hpp"

#include "InputEnum.hpp"

namespace Nano
{
    struct InputEventMapping
    {
        StringID event = StringID::Empty();
        InputKey key = InputKey::_None;
        CustomInputType inputType = CustomInputType::_Click;
        InputKey modifyKey1 = InputKey::_None;
        InputKey modifyKey2 = InputKey::_None;

        union
        {
            float holdTime = 1.0f;
        };
    };

    struct InputScheme
    {
        StringID schemeName{ StringID::Empty() };
        Vector<InputEventMapping> inputEventMappings;
    };
}