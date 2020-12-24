#include "NanoEngine/Common/CommonGlobalContext.hpp"
#include "NanoEngine/Common/Thread/TaskManager.hpp"
#include "NanoEngine/Common/CSDelegate/CSDelegate.hpp"

namespace Nano
{
    //CommonGlobalContext g_CommonGloablContext;
}

Nano::CommonGlobalContext::~CommonGlobalContext()
{
    delete m_TaskManager;
    delete m_CSDelegate;
}

bool Nano::CommonGlobalContext::Init()
{
    m_TaskManager = new TaskManager();
    m_CSDelegate = new CSDelegate();

    m_TaskManager->Init();
    m_CSDelegate->Init();
    return true;
}

void Nano::CommonGlobalContext::Close()
{
    m_TaskManager->Close();
    m_CSDelegate->Close();
}

void Nano::CommonGlobalContext::Update(float dt)
{
}