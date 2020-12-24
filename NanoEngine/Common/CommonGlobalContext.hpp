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
        class CSDelegate* m_CSDelegate;
    };

    //extern CommonGlobalContext g_CommonGloablContext;
}