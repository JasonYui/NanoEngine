#pragma once
#include "common/type/type_def.hpp"

namespace Nano
{
    struct WindowDefination
    {
        const char* appName = "NanoEngine";
        uint32_t screenWidth = 400;
        uint32_t screenHeight = 300;

        WindowDefination() = default;
        WindowDefination(const char* name, uint32_t width, uint32_t height) :
            appName(name), screenWidth(width), screenHeight(height) {}
    };
}