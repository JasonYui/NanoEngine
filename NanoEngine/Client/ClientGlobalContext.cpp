#include "ClientGlobalContext.hpp"

namespace Nano
{
    ClientGlobalContext g_ClientGlobalContext = ClientGlobalContext();
}

bool Nano::ClientGlobalContext::Init()
{
    if (!CommonGlobalContext::Init())
        return false;
    return true;
}

void Nano::ClientGlobalContext::Close()
{
    CommonGlobalContext::Close();
}

void Nano::ClientGlobalContext::Update(float dt)
{
    CommonGlobalContext::Update(dt);
}
