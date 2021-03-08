#include "common/type/type_def.hpp"
#include "client/main/client_main.hpp"

using namespace Nano;
int main()
{
    LOG_INFO("game start");
    ClientDesc desc = {};
    desc.windowDef = WindowDefination("TestGame", 400, 300);
    desc.tickMode = TickMode::_Fixed;
    desc.frameRate = 60;
    Nano::ClientMain(desc);
}