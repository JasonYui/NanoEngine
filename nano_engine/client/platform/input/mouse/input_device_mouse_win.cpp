#include "common/fwd.hpp"

#include "client/main/client_global_context.hpp"
#include "client/platform/input/mouse/input_device_mouse_win.hpp"
#include "client/platform/application/win/win_application.hpp"

namespace Nano
{
    InputDeviceMouseWin::InputDeviceMouseWin()
    {
        const WinApplication* app = static_cast<const WinApplication*>(g_ClientGlobalContext.GetApplication());
        if (app)
        {
            app->SetMouseMsgHandler(std::bind(&InputDeviceMouseWin::HandleMessage, this, std::placeholders::_1));
        }
    }

    void InputDeviceMouseWin::HandleMessage(const MSG& msg)
    {
        if (msg.message != WM_INPUT)
        {
            return;
        }

        uint32_t dwSize = 0;
        GetRawInputData((HRAWINPUT)msg.lParam, RID_INPUT, nullptr, &dwSize, sizeof(RAWINPUTHEADER));

        LPBYTE lpb = new BYTE[dwSize];
        if (lpb == nullptr)
        {
            return;
        }

        GetRawInputData((HRAWINPUT)msg.lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));
        RAWINPUT* raw = (RAWINPUT*)lpb;

        if (raw->header.dwType == RIM_TYPEMOUSE)
        {
            if (raw->data.mouse.usFlags == MOUSE_MOVE_RELATIVE)
            {
                Vector2f prev = Vector2f::Zero();
                GetAxisKey(InputKey::_MouseAxisXY, prev);
                HandleAxis(InputKey::_MouseAxisXY, prev + Vector2f(float(raw->data.mouse.lLastX), float(raw->data.mouse.lLastY)));
#ifdef ENGINE_DEBUG
                LOG_INFO("mouse position x:{0:f}, y:{0:f}", prev.x + float(raw->data.mouse.lLastX), prev.y + float(raw->data.mouse.lLastY));
#endif
            }
            else if (raw->data.mouse.usFlags & MOUSE_MOVE_ABSOLUTE)
            {
                HandleAxis(InputKey::_MouseAxisXY, Vector2f(float(raw->data.mouse.lLastX), float(raw->data.mouse.lLastY)));
            }

            if (raw->data.mouse.usButtonFlags == RI_MOUSE_WHEEL)
            {
                if (SHORT(raw->data.mouse.usButtonData) < 0)
                {
                    HandleButton(InputKey::_MouseButtonWheelDown, true);
                }
                else if (SHORT(raw->data.mouse.usButtonData) > 0)
                {
                    HandleButton(InputKey::_MouseButtonWheelUp, true);
                }
            }
            else
            {
                if (raw->data.mouse.usButtonFlags & RI_MOUSE_BUTTON_1_DOWN)
                {
                    HandleButton(InputKey::_MouseButton0, true);
                }
                if (raw->data.mouse.usButtonFlags & RI_MOUSE_BUTTON_1_UP)
                {
                    HandleButton(InputKey::_MouseButton0, false);
                }

                if (raw->data.mouse.usButtonFlags & RI_MOUSE_BUTTON_2_DOWN)
                {
                    HandleButton(InputKey::_MouseButton1, true);
                }
                if (raw->data.mouse.usButtonFlags & RI_MOUSE_BUTTON_2_UP)
                {
                    HandleButton(InputKey::_MouseButton1, false);
                }

                if (raw->data.mouse.usButtonFlags & RI_MOUSE_BUTTON_3_DOWN)
                {
                    HandleButton(InputKey::_MouseButton2, true);
                }
                if (raw->data.mouse.usButtonFlags & RI_MOUSE_BUTTON_3_UP)
                {
                    HandleButton(InputKey::_MouseButton2, false);
                }

                if (raw->data.mouse.usButtonFlags & RI_MOUSE_BUTTON_4_DOWN)
                {
                    HandleButton(InputKey::_MouseButton5, true);
                }
                if (raw->data.mouse.usButtonFlags & RI_MOUSE_BUTTON_4_UP)
                {
                    HandleButton(InputKey::_MouseButton5, false);
                }

                if (raw->data.mouse.usButtonFlags & RI_MOUSE_BUTTON_5_DOWN)
                {
                    HandleButton(InputKey::_MouseButton6, true);
                }
                if (raw->data.mouse.usButtonFlags & RI_MOUSE_BUTTON_5_UP)
                {
                    HandleButton(InputKey::_MouseButton6, false);
                }
            }
        }
    }
}