#pragma once

#include "Common/Tick/TickManager.hpp"
#include "Client/Application/WindowDefination.hpp"

namespace Nano
{
    struct ClientDesc
    {
        WindowDefination windowDef;
        TickMode tickMode{ TickMode::_Fixed };
        uint32_t frameRate{ 30 };
    };
}