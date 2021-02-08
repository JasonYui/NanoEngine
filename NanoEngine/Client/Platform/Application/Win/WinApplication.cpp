#include "WinApplication.hpp"
#include "Common/Type/TypeDef.hpp"
#include "Client/ClientGlobalContext.hpp"
#include "Client/Input/InputManager.hpp"
#include "Client/Platform/Input/Keyboard/InputDeviceKeyboardWin.hpp"
#include "Client/Platform/Input/Mouse/InputDeviceMouseWin.hpp"

namespace Nano
{
    bool WinApplication::Init()
    {
        return true;
    }

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
        ::ShowWindow(m_HWnd, SW_SHOW);
        ::UpdateWindow(m_HWnd);
        CreateRawInputDevice();
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
            MSG msg;
            msg.lParam = lParam;
            msg.message = WM_INPUT;
            if (self->m_KeyboardMsgHandler != nullptr)
            {
                self->m_KeyboardMsgHandler(msg);
            }

            if (self->m_MouseMsgHandler != nullptr)
            {
                self->m_MouseMsgHandler(msg);
            }

        }break;
        default:
            result = DefWindowProc(hWnd, message, wParam, lParam);
        }

        return result;
    }
    
    void WinApplication::CreateRawInputDevice()
    {
        uint32_t deviceNum = 0;
        if (GetRawInputDeviceList(nullptr, &deviceNum, sizeof(RAWINPUTDEVICELIST)) != 0)
        {
            LOG_ERROR("call GetRawInputDeviceList failed");
            return;
        }

        PRAWINPUTDEVICELIST rawDevices = (PRAWINPUTDEVICELIST)malloc(sizeof(RAWINPUTDEVICELIST) * deviceNum);
        if (rawDevices == nullptr)
        {
            LOG_ERROR("malloc PRAWINPUTDEVICELIST failed");
            return;
        }

        if (GetRawInputDeviceList(rawDevices, &deviceNum, sizeof(RAWINPUTDEVICELIST)) == -1)
        {
            LOG_ERROR("call GetRawInputDeviceList failed");
            return;
        }

        const InputManager* inputMgr = g_ClientGlobalContext.GetInputManager();

        bool findKeyboard = false;
        bool findMouse = false;
        for (uint32_t index = 0; index < deviceNum; ++index)
        {
            if ((rawDevices + index)->dwType == RIM_TYPEKEYBOARD)
                findKeyboard = true;
            else if ((rawDevices + index)->dwType == RIM_TYPEMOUSE)
                findMouse = true;
        }

        free(rawDevices);

        uint32_t availableDeviceCOunt = static_cast<uint32_t>(findKeyboard) + static_cast<uint32_t>(findMouse);
        RAWINPUTDEVICE* rawinputDevices = new RAWINPUTDEVICE[availableDeviceCOunt]();

        uint32_t index = 0;
        if (findKeyboard)
        {
            inputMgr->CreateDevice<InputDeviceKeyboardWin>();

            (rawinputDevices + index)->usUsagePage = 0x01;
            (rawinputDevices + index)->usUsage = 0x06;
            (rawinputDevices + index)->dwFlags = RIDEV_INPUTSINK;
            (rawinputDevices + index)->hwndTarget = m_HWnd;
            index++;
        }

        if (findMouse)
        {
            inputMgr->CreateDevice<InputDeviceMouseWin>();

            (rawinputDevices + index)->usUsagePage = 0x01;
            (rawinputDevices + index)->usUsage = 0x02;
            (rawinputDevices + index)->dwFlags = 0;
            (rawinputDevices + index)->hwndTarget = m_HWnd;
            index++;
        }

        if (!RegisterRawInputDevices(rawinputDevices, index, sizeof(RAWINPUTDEVICE)))
        {
            LOG_WARNING("register keyboard raw input failed");
        }
    }
}
