#include "Common/Tick/TickManager.hpp"

#include "ClientGlobalContext.hpp"
#include "Client/Input/InputManager.hpp"

#ifdef _WINDOWS
#include "Client/Platform/Application/Win/WinApplication.hpp"
#include "Client/Platform/RHI/Win/D3DGraphicsManager.hpp"
#endif

namespace Nano
{
    ClientGlobalContext g_ClientGlobalContext = ClientGlobalContext();

    ClientGlobalContext::ClientGlobalContext()
    {
        m_TickManager = new TickManager();
        m_InputManager = new InputManager();
#ifdef _WINDOWS
        m_Application = new WinApplication();
        m_GfxManager = new D3dGraphicsManager();
#endif
    }

    ClientGlobalContext::~ClientGlobalContext()
    {
        delete m_GfxManager;
        m_GfxManager = nullptr;

        delete m_Application;
        m_Application = nullptr;

        delete m_InputManager;
        m_InputManager = nullptr;

        delete m_TickManager;
        m_TickManager = nullptr;
    }

    bool ClientGlobalContext::Init(const ClientDesc& desc)
    {
        if (!m_TickManager->Init(desc.tickMode, desc.frameRate))
        {
            LOG_ERROR("meet error when init TickManager");
            return false;
        }

        if (!m_InputManager->Init())
        {
            LOG_ERROR("meet error when init InputManager");
            return false;
        }

        if (!m_Application->Init())
        {
            LOG_ERROR("meet error when init Application");
            return false;
        }

        m_Application->CreateDisplayWindow(desc.windowDef);

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
        m_Application->Close();
        m_InputManager->Close();
        m_TickManager->Close();
    }

    void ClientGlobalContext::Update()
    {
        float dt = 0.0f;
        m_Application->Update(dt);
        if (!m_TickManager->TryGetDeltaTime(dt))
            return;

        m_InputManager->Update(dt);
        //LOG_INFO("delta time = {0:f}", dt);
    }
}

