#include "ClientMain.hpp"
#include "Client/Application/Application.hpp"

namespace Nano
{
    extern int ClientMain(const WindowDefination& windowDef)
    {
        const IApplication* app = g_ClientGlobalContext.GetApplication();
        if (g_ClientGlobalContext.Init(windowDef))
        {
            while (!app->IsQuit())
            {
                g_ClientGlobalContext.Update(0);
            }
        }
        g_ClientGlobalContext.Close();

        return 0;
    }
}