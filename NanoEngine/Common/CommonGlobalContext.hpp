#pragma once

namespace Nano
{
    class CommonGlobalContext
    {
    public:
        ~CommonGlobalContext();
        bool Init();
        void Close();
        void Update(float dt);
    public:
        class TaskManager* m_TaskManager;
    };

    extern CommonGlobalContext g_CommonGloablContext;
}