#include "Common.h"
#include "GameServer.h"

int main(int argc, char const *argv[])
{
    GameEngine::GameServer server;

    server.run();
    return 0;
}
