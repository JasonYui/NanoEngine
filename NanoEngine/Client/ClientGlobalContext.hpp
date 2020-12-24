#pragma once
#include "NanoEngine/Common/CommonGlobalContext.hpp"

namespace Nano
{
    class ClientGlobalContext : CommonGlobalContext
    {
    public:
        bool Init();
        void Close();
        void Update(float dt);
    };

    extern ClientGlobalContext g_ClientGlobalContext;
}