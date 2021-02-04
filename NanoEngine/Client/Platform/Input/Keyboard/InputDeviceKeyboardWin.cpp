#include "InputDeviceKeyboardWin.hpp"
#include "Common/Fwd.hpp"

namespace Nano
{
    void InputDeviceKeyboardWin::HandleMessage(const MSG& msg)
    {
        if (msg.message != WM_INPUT)
        {
            return;
        }

        uint32_t dwSize = 40;
        static ubyte lpb[40];
        
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

            if (g_KeyMapping.count(vkey))
            {
                const Key key = g_KeyMapping[vkey];
#ifdef ENGINE_DEBUG
                LOG_INFO("{0:d} mapped to: {1:d}", vkey, static_cast<uint32_t>(key));
#endif
                const bool pressed = raw->data.keyboard.Message == WM_KEYDOWN || raw->data.keyboard.Message == WM_SYSKEYDOWN;
                //HandleButton(device_, nextState_, delta_, buttonId, pressed);
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