#include "WinApplication.hpp"
#include "Common/Type/TypeDef.hpp"

namespace Nano
{
    void WinApplication::Update(float dt)
    {
        MSG msg;
        // we use PeekMessage instead of GetMessage here
        // because we should not block the thread at anywhere
        // except the engine execution driver module
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // translate keystroke messages into the right format
            TranslateMessage(&msg);

            // send the message to the WindowProc function
            DispatchMessage(&msg);
        }
    }

    void WinApplication::CreateDisplayWindow(const WindowDefination& define)
    {
        HINSTANCE hInstance = GetModuleHandle(NULL);

        // this struct holds information for the window class
        WNDCLASSEX wc;

        // clear out the window class for use
        ZeroMemory(&wc, sizeof(WNDCLASSEX));

        // fill in the struct with the needed information
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = WindowProcess;
        wc.hInstance = hInstance;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
        wc.lpszClassName = "NanoEngine_Client";

        // register the window class
        RegisterClassEx(&wc);

        int heightAdjust = (GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CXPADDEDBORDER));
        int widthAdjust = (GetSystemMetrics(SM_CXFRAME) + GetSystemMetrics(SM_CXPADDEDBORDER));

        // create the window and use the result as the handle
        m_HWnd = CreateWindowEx(
            0,
            "NanoEngine_Client",                        // name of the window class
            define.appName,                             // title of the window
            WS_OVERLAPPEDWINDOW,                        // window style
            CW_USEDEFAULT,                              // x-position of the window
            CW_USEDEFAULT,                              // y-position of the window
            define.screenWidth + widthAdjust,           // width of the window
            define.screenHeight + heightAdjust,         // height of the window
            NULL,                                       // we have no parent window, NULL
            NULL,                                       // we aren't using menus, NULL
            hInstance,                                  // application handle
            this);                                      // pass pointer to current object

        m_HDC = GetDC(m_HWnd);

        // display the window on the screen
        ShowWindow(m_HWnd, SW_SHOW);
        UpdateWindow(m_HWnd);

        RAWINPUTDEVICE rawInputDevice;

        //The HID standard for mouse
        const uint16_t standardMouse = 0x02;

        rawInputDevice.usUsagePage = 0x01;
        rawInputDevice.usUsage = standardMouse;
        rawInputDevice.dwFlags = 0;

        // Process input for just the window that requested it.  NOTE: If we pass NULL here events are routed to the window with keyboard focus
        // which is not always known at the HWND level with Slate
        rawInputDevice.hwndTarget = m_HWnd;

        // Register the raw input device
        ::RegisterRawInputDevices(&rawInputDevice, 1, sizeof(RAWINPUTDEVICE));
    }

    void WinApplication::GetWindowSize(OUT uint32_t& width, OUT uint32_t& height) const
    {
        width = m_WindowDef.screenWidth;
        height = m_WindowDef.screenHeight;
    }

    LRESULT CALLBACK WinApplication::WindowProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        LRESULT result = 0;

        WinApplication* self;
        if (message == WM_NCCREATE)
        {
            self = static_cast<WinApplication*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);

            SetLastError(0);
            if (!SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(self)))
            {
                if (GetLastError() != 0) 
                    return FALSE;
            }
        }
        else
        {
            self = reinterpret_cast<WinApplication*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
        }

        // sort through and find what code to run for the message given
        switch (message)
        {
        case WM_DESTROY:
        {

            PostQuitMessage(0);
            self->m_IsQuit = true;
        } break;
        case WM_KEYDOWN:
        {
        }
        break;
        case WM_INPUT:
        {
        }break;
        default:
            result = DefWindowProc(hWnd, message, wParam, lParam);
        }

        return result;
    }
}
