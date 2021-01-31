#pragma once
#include "Client/Application/WindowDefination.hpp"

namespace Nano
{
    class IApplication;
    class GraphicsManager;

    class ClientGlobalContext
    {
    public:
        ClientGlobalContext();
        ~ClientGlobalContext();
        bool Init(const WindowDefination& windowDef);
        void Close();
        void Update(float dt);

        const IApplication* GetApplication() const { return m_Application; }
        const GraphicsManager* GetGraphicsManager() const { return m_GfxManager; }

    private:
        IApplication* m_Application;
        GraphicsManager* m_GfxManager;
    };

    extern ClientGlobalContext g_ClientGlobalContext;
}