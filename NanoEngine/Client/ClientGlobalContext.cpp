#include "ClientGlobalContext.hpp"

namespace Nano
{
    ClientGlobalContext g_ClientGlobalContext = ClientGlobalContext();
}

bool Nano::ClientGlobalContext::Init()
{
    return true;
}

void Nano::ClientGlobalContext::Close()
{
}

void Nano::ClientGlobalContext::Update(float dt)
{
}
