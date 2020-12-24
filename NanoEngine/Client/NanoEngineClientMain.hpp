#pragma once
#include "NanoEngine/Client/ClientGlobalContext.hpp"

namespace Nano
{
    int ClientMain()
    {
        g_ClientGlobalContext.Init();
        g_ClientGlobalContext.Close();
        return 0;
    }
}