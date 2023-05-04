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

    virtual void onNewClient(void *payload)
    {
    }

    virtual void onClientDisconnected(void *payload)
    {
    }
    virtual void onClientInput(void *payload)
    {
    }

    void gameLogic();

    json getGameStates();
};

} // namespace GameEngine
