#pragma once

namespace Nano
{
    class ClientGlobalContext
    {
    public:
        bool Init();
        void Close();
        void Update(float dt);
    };

    extern ClientGlobalContext g_ClientGlobalContext;
}