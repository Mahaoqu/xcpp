#include "GameServer.h"
#include "Network.h"

namespace GameEngine
{

GameServer::GameServer() : context(1)
{
}

GameServer::~GameServer()
{
}

void GameServer::newHandleClientThread()
{
    std::thread t([&]() {
        zmq::socket_t rep(context, zmq::socket_type::rep);
        rep.bind("tcp://*:5555");

        while (true)
        {
            zmq::message_t request;
            rep.recv(request, zmq::recv_flags::none);

            if (request.size() == 0)
                continue;

            char *data = static_cast<char *>(request.data());

            PacketType type = static_cast<PacketType>(data[0]);

            switch (type)
            {
            case PacketType::PT_HELLO:
                break;

            case PacketType::PT_INPUT:
                break;

            case PacketType::PT_DISCONNECT:
                break;

            default:
                break;
            }
        }
    });
    t.detach();
}

void GameServer::addObject(GameObject *obj)
{
    GameObject::game_objects.push_back(obj);
}

void GameServer::run()
{
    std::cout << "Running Game Server at port " << port << std::endl;

    zmq::socket_t publisher(context, zmq::socket_type::pub);
    publisher.bind("tcp://*:5556");

    // Init game state

    // Recv client
    newHandleClientThread();

    while (true)
    {
        // Update clock
        tl.addNewKeyFrame();
        // Run game logic
        gameLogic();

        // Publish game state
        std::string game_state = getGameStates();
        publisher.send(zmq::message_t(game_state));

        std::cout << "Sending game state " << game_state.size() << " bytes." << std::endl;

        // Sleep
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
    }
}

void GameServer::gameLogic()
{
    for (auto obj : GameObject::game_objects)
    {
        obj->update(tl);
    }
}

std::string GameServer::getGameStates()
{
    return std::string();
}

} // namespace GameEngine
