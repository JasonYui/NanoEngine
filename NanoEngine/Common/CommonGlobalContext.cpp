#include "NanoEngine/Common/CommonGlobalContext.hpp"
#include "NanoEngine/Common/Thread/TaskManager.hpp"

namespace Nano
{
    CommonGlobalContext g_CommonGloablContext;
}

Nano::CommonGlobalContext::~CommonGlobalContext()
{
    delete m_TaskManager;
}

bool Nano::CommonGlobalContext::Init()
{
    m_TaskManager = new TaskManager();

    m_TaskManager->Init();
    return true;
}

void Nano::CommonGlobalContext::Close()
{
    m_TaskManager->Close();
}

void Nano::CommonGlobalContext::Update(float dt)
{
}