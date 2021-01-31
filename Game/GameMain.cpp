#include "Client/ClientMain.hpp"
#include "Client/ClientGlobalContext.hpp"
#include "Client/Application/WindowDefination.hpp"
#include "Common/Type/TypeDef.hpp"

using namespace Nano;
int main()
{
    LOG_INFO("game start")
    WindowDefination windowDef("TestGame", 400, 300);
    Nano::ClientMain(windowDef);
}