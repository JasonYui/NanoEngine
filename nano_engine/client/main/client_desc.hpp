#pragma once

#include "common/tick/tick_manager.hpp"
#include "client/application/window_defination.hpp"

namespace Nano
{
    struct ClientDesc
    {
        WindowDefination windowDef;
        TickMode tickMode{ TickMode::_Fixed };
        uint32_t frameRate{ 30 };
    };
}