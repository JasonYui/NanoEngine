#pragma once
#include "Client/Application/WindowDefination.hpp"

namespace Nano
{
    class InputManager;
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

        const InputManager* GetInputManager() const { return m_InputManager; }
        const IApplication* GetApplication() const { return m_Application; }
        const GraphicsManager* GetGraphicsManager() const { return m_GfxManager; }

    private:
        InputManager* m_InputManager{ nullptr };
        IApplication* m_Application{ nullptr };
        GraphicsManager* m_GfxManager{ nullptr };
    };

    extern ClientGlobalContext g_ClientGlobalContext;
}