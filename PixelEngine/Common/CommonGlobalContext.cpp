#include "PixelEngine/Common/CommonGlobalContext.hpp"
#include "PixelEngine/Common/Thread/TaskManager.hpp"

namespace Pixel
{
    CommonGlobalContext g_CommonGloablContext;
}

Pixel::CommonGlobalContext::~CommonGlobalContext()
{
    delete m_TaskManager;
}

bool Pixel::CommonGlobalContext::Init()
{
    m_TaskManager = new TaskManager();

    m_TaskManager->Init();
    return true;
}

void Pixel::CommonGlobalContext::Close()
{
    m_TaskManager->Close();
}

void Pixel::CommonGlobalContext::Update(float dt)
{
}