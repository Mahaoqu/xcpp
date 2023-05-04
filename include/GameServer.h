#pragma once

#include "GameObject.h"

namespace GameEngine
{

class GameServer
{
  private:
    zmq::context_t context;
    int port = 5555;

    Timeline tl;

  public:
    GameServer(/* args */);
    ~GameServer();

    void newHandleClientThread();
    void addObject(GameObject *obj);
    void run();

    void gameLogic();

    std::string getGameStates();
};

} // namespace GameEngine
