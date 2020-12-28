#include "NanoEngine/Client/NanoEngineClientMain.hpp"

namespace Nano
{
    extern int ClientMain()
    {
        g_ClientGlobalContext.Init();
        g_ClientGlobalContext.Close();
        return 0;
    }
}