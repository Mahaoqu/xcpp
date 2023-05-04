#include "GameServer.h"
#include "GameObjectManager.h"
#include "NetworkManager.h"

namespace GameEngine
{

GameServer::GameServer() : context(1), rep(context, zmq::socket_type::rep)
{
}

GameServer::~GameServer()
{
}

void GameServer::newHandleClientThread()
{
    std::thread t([&]() {
        rep.bind("tcp://*:" + std::to_string(port));
        std::cout << "Binding at port: " << port << std::endl;

        while (true)
        {
            try
            {
                zmq::message_t request;
                rep.recv(&request);
                LOG("Received request");

                if (request.size() == 0)
                    continue;

                char *data = static_cast<char *>(request.data());

                PacketType type = static_cast<PacketType>(data[0]);

                json j, q;
                std::stringstream ss(data + 1, request.size() - 1);
                if (request.size() > 1)
                    ss >> j;

                switch (type)
                {
                case PacketType::PT_HELLO:
                    q = onNewClient(j);
                    break;

                case PacketType::PT_INPUT:
                    q = onClientInput(j);
                    break;

                case PacketType::PT_DISCONNECT:
                    q = onClientDisconnected(j);
                    break;

                default:
                    std::cerr << "Invalid packet type received." << std::endl;
                    break;
                }
                std::string s = Network::setWelcomePacket(q);
                rep.send(zmq::message_t(s));
            }
            catch (const zmq::error_t &e)
            {
                std::cerr << "ZeroMQ error: " << e.what() << std::endl;
            }
            catch (std::exception &e)
            {
                std::cerr << "Exception: " << e.what() << std::endl;
            }
            catch (...)
            {
                std::cerr << "Unknown exception" << std::endl;
            }
        }
    });
    t.detach();
}

void GameServer::addObject(GameObject *obj)
{
    GameObjectManager::Get().add(obj);
}

void GameServer::run()
{
    zmq::socket_t publisher(context, zmq::socket_type::pub);
    publisher.bind("tcp://*:" + std::to_string(publish_port));
    std::cout << "Binding publish at port: " << publish_port << std::endl;

    // Init game state
    beforeServerStart();

    // Recv client
    newHandleClientThread();

    while (true)
    {
        // Update clock
        tl.newFrame();
        // Run game logic
        gameLogic();

        // Publish game state / publish game event
        std::string game_state;
        game_state += (char)PacketType::PT_WORLDSTATE;
        game_state += getGameStates().dump();
        publisher.send(zmq::message_t(game_state));

        // Sleep
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
    }
}

void GameServer::gameLogic()
{
    // update logics
    GameObjectManager::Get().forEach([&](GameObject *obj) { obj->update(tl); });
}

json GameServer::getGameStates()
{
    json j;
    j["frame"] = tl.getFrameCount();
    json objs = GameObjectManager::Get().toJSON();
    j["objects"] = objs;
    return j;
}

} // namespace GameEngine
