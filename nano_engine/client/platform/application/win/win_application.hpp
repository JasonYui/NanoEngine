#pragma once
#include <windows.h>
#include <windowsx.h>
#include <functional>
#include "client/application/application.hpp"

namespace Nano
{
    class WinApplication : public IApplication
    {
    public:
        WinApplication() = default;
        ~WinApplication();
        bool Init();
        void Update(float dt) final;

        void CreateDisplayWindow(const WindowDefination& define) final;
        bool IsQuit() const final { return m_IsQuit; }
        void GetWindowSize(OUT uint32_t& width, OUT uint32_t& height) const final;

        //platform only api
        HWND GetHWND() const { return m_HWnd; }
        void SetKeyboardMsgHandler(std::function<void(MSG)> handler) const { m_KeyboardMsgHandler = handler; }
        void SetMouseMsgHandler(std::function<void(MSG)> handler) const { m_MouseMsgHandler = handler; }
    private:
        static LRESULT CALLBACK WindowProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

        void CreateRawInputDevice();
    private:
        HWND m_HWnd{ nullptr };
        HDC m_HDC{ nullptr };
        bool m_IsQuit{ false };
        WindowDefination m_WindowDef;
        mutable std::function<void(MSG)> m_KeyboardMsgHandler;
        mutable std::function<void(MSG)> m_MouseMsgHandler;
    };
}