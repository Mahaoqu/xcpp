#pragma once

#include "GameObject.h"

namespace GameEngine
{

class GameServer
{
  private:
    zmq::context_t context;
    zmq::socket_t rep;
    int port = 5555;
    int publish_port = 5556;

    Timeline tl;

  public:
    GameServer();
    ~GameServer();

    void newHandleClientThread();
    void addObject(GameObject *obj);
    void run();

    virtual void beforeServerStart()
    {
    }

    virtual json onNewClient(json nc)
    {
        return json();
    }

    virtual json onClientDisconnected(json cd)
    {
        return json();
    }

    virtual json onClientInput(json input)
    {
        return json();
    }

    void gameLogic();

    json getGameStates();
};

} // namespace GameEngine
