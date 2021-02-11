#include "ClientMain.hpp"
#include "Client/Application/Application.hpp"

namespace Nano
{
    extern int ClientMain(const ClientDesc& desc)
    {
        const IApplication* app = g_ClientGlobalContext.GetApplication();
        if (g_ClientGlobalContext.Init(desc))
        {
            while (!app->IsQuit())
            {
                g_ClientGlobalContext.Update();
            }
        }
        g_ClientGlobalContext.Close();

        return 0;
    }
}