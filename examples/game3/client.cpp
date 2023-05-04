#include "GameClient.h"
#include "game.h"

int main(int argc, char const *argv[])
{
    GameEngine::GameClient gc;

    RegisterGameObjectClasses();
    gc.set_connect_to_server(true);

    gc.init();
    gc.run();

    exit(0);
}
