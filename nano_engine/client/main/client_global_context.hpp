#pragma once

#include "common/type/memory_wrapper.hpp"
#include "client/main/client_desc.hpp"

namespace Nano
{
    class TickManager;
    class InputManager;
    class IApplication;
    class GraphicsManager;

    class ClientGlobalContext
    {
    public:
        ClientGlobalContext();
        ~ClientGlobalContext();
        bool Init(const ClientDesc& desc);
        void Close();
        void Update();

        const InputManager* GetInputManager() const { return m_InputManager; }
        const IApplication* GetApplication() const { return m_Application; }
        const GraphicsManager* GetGraphicsManager() const { return m_GfxManager; }

    private:
        TickManager* m_TickManager{ nullptr };
        InputManager* m_InputManager{ nullptr };
        IApplication* m_Application{ nullptr };
        GraphicsManager* m_GfxManager{ nullptr };
    };

    extern ClientGlobalContext g_ClientGlobalContext;
}