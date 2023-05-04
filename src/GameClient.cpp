#include "GameClient.h"
#include "GameObjectManager.h"

namespace GameEngine
{

void GameClient::render()
{
    window.clear();
    for (auto obj : GameObjectManager::Get().getObjects())
    {
        obj->render(window);
    }

    window.display();
}

void GameClient::newHandleServerThread()
{
    if (is_connnect_to_server)
    {
        std::thread network_thread([&]() {
            // connect to server
            std::cout << "Connecting to server at " << this->server_addr << std::endl;

            zmq::socket_t req(context, zmq::socket_type::req);
            req.connect("tcp://" + this->server_addr + ":" + std::to_string(this->port));

            // send hello packet
            auto hello_packet = Network::setHelloPacket();
            req.send(zmq::message_t(hello_packet));

            // get reply
            zmq::message_t reply;
            req.recv(&reply);
            json j = Network::parseFromWelcomePacket((char *)reply.data(), reply.size());
            this->client_id = j["id"];

            state = NetworkClientState::NCS_SayingHello;

            // receive game state
            while (true)
            {
            }
        });

        network_thread.detach();
    }
}

void GameClient::handleKeyPress(sf::Keyboard::Key key)
{
    this->pressed_keys.insert(key);
}

void GameClient::handleKeyRelease(sf::Keyboard::Key key)
{
    this->pressed_keys.erase(key);
}

GameClient::GameClient() : context(1)
{
}

GameClient::~GameClient()
{
}

void GameClient::init()
{
    window.create(sf::VideoMode(width, height), game_title_name);
    window.setFramerateLimit(60);
}

void GameClient::run()
{
    // add network thread
    newHandleServerThread();

    window.setActive();

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Handle input
            else if (event.type == sf::Event::KeyPressed)
                handleKeyPress(event.key.code);

            else if (event.type == sf::Event::KeyReleased)
                handleKeyRelease(event.key.code);
        }

        render();
    }
}

void GameClient::addToScene(GameObject *obj)
{
    GameObjectManager::Get().add(obj);
}

void GameClient::handleGameState(json j)
{
    j["time"];
    json objs = j["objects"];

    GameObjectManager::Get().fromJSON(objs);
}

} // namespace GameEngine
