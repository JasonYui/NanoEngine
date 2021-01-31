#include "ClientGlobalContext.hpp"

#ifdef _WINDOWS
#include "Client/Platform/Application/Win/WinApplication.hpp"
#include "Client/Platform/RHI/Win/D3DGraphicsManager.hpp"
#endif

namespace Nano
{
    ClientGlobalContext g_ClientGlobalContext = ClientGlobalContext();

    ClientGlobalContext::ClientGlobalContext()
    {
#ifdef _WINDOWS
        m_Application = new WinApplication();
        m_GfxManager = new D3dGraphicsManager();
#endif
    }

    ClientGlobalContext::~ClientGlobalContext()
    {
        Close();
    }

    bool ClientGlobalContext::Init(const WindowDefination& windowDef)
    {
        if (!m_Application->Init())
        {
            LOG_ERROR("meet error when init Application");
            return false;
        }

        m_Application->CreateDisplayWindow(windowDef);

        if (!m_GfxManager->Init())
        {
            LOG_ERROR("meet error when init GraphicsManager");
            return false;
        }
        return true;
    }

    void ClientGlobalContext::Close()
    {
        m_GfxManager->Close();
        delete m_GfxManager;
        m_GfxManager = nullptr;

        m_Application->Close();
        delete m_Application;
        m_Application = nullptr;
    }

    void ClientGlobalContext::Update(float dt)
    {
        m_Application->Update(dt);
    }
}

