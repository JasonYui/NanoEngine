
#include <functional>
#include "common/fwd.hpp"

#include "client/platform/input/keyboard/input_device_keyboard_win.hpp"
#include "client/main/client_global_context.hpp"
#include "client/platform/application/win/win_application.hpp"

namespace Nano
{
    const HashMap<uint32_t, InputKey> InputDeviceKeyboardWin::s_KeyMapping = {
        { VK_ESCAPE, InputKey::_KeyEscape },
        { VK_F1, InputKey::_KeyF1 },
        { 'W', InputKey::_KeyW },
        { 'A', InputKey::_KeyA },
        { 'S', InputKey::_KeyS },
        { 'D', InputKey::_KeyD },
        { VK_LCONTROL, InputKey::_KeyCtrlL },
        { VK_LSHIFT, InputKey::_KeyShiftL }
    };

    InputDeviceKeyboardWin::InputDeviceKeyboardWin()
    {
        const WinApplication* app = static_cast<const WinApplication*>(g_ClientGlobalContext.GetApplication());
        if (app)
        {
            app->SetKeyboardMsgHandler(std::bind(&InputDeviceKeyboardWin::HandleMessage, this, std::placeholders::_1));
        }
    }

    void InputDeviceKeyboardWin::HandleMessage(const MSG& msg)
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
        
        if (raw->header.dwType == RIM_TYPEKEYBOARD) 
        {
            uint16_t vkey = raw->data.keyboard.VKey;

            if (vkey == VK_CONTROL)
            {
                if (raw->data.keyboard.Flags & RI_KEY_E0)
                    vkey = VK_RCONTROL;
                else
                    vkey = VK_LCONTROL;
            }
            else if (vkey == VK_SHIFT)
            {
                if (raw->data.keyboard.MakeCode == 0x36)
                    vkey = VK_RSHIFT;
                else
                    vkey = VK_LSHIFT;
            }
            else if (vkey == VK_MENU)
            {
                if (raw->data.keyboard.Flags & RI_KEY_E0)
                    vkey = VK_RMENU;
                else
                    vkey = VK_LMENU;
            }

            if (s_KeyMapping.count(vkey))
            {
                const InputKey key = s_KeyMapping.at(static_cast<uint32_t>(vkey));
#ifdef ENGINE_DEBUG
                LOG_INFO("{0:d} mapped to: {1:d}", vkey, static_cast<uint32_t>(key));
#endif
                const bool down = raw->data.keyboard.Message == WM_KEYDOWN || raw->data.keyboard.Message == WM_SYSKEYDOWN;
                HandleButton(key, down);
            }
#ifdef ENGINE_DEBUG
            else
            {
                LOG_INFO("unmapped raw vkey: {0:d}", vkey);
            }
#endif
        }
    }
}