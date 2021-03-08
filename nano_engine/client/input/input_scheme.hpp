#pragma once
#include "common/fwd.hpp"
#include "common/type/string_id.hpp"
#include "common/type/array_wrapper.hpp"

#include "client/input/input_enum.hpp"

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