#include "GameClient.h"
#include "GameObjectManager.h"

namespace GameEngine
{

void GameClient::render()
{
    window.clear();
    GameObjectManager::Get().forEach([&](GameObject *obj) { obj->render(window); });
    
    window.display();
}

void GameClient::newHandleServerThread()
{
    if (is_connnect_to_server)
    {
        std::thread network_thread([&]() {
            // connect to server
            req.connect("tcp://" + this->server_addr + ":" + std::to_string(this->port));
            std::cerr << "Connecting to server at " << this->server_addr << ":" << this->port << std::endl;

            zmq::socket_t sub(context, zmq::socket_type::sub);
            sub.connect("tcp://" + this->server_addr + ":" + std::to_string(this->publish_port));
            sub.setsockopt(ZMQ_SUBSCRIBE, "", 0);
            std::cerr << "Connecting to server at " << this->server_addr << ":" << this->publish_port << std::endl;

            // send hello packet
            auto hello_packet = Network::setHelloPacket();
            req.send(zmq::message_t(hello_packet));

            // get reply
            zmq::message_t reply;
            req.recv(&reply);

            // std::stringstream ss("{\"id\": 0}");
            std::string ss(static_cast<char *>(reply.data()) + 1, reply.size() - 1);
            json j;
            try
            {
                j = json::parse(ss);
            }
            catch (json::parse_error &ex)
            {
                std::cerr << "parse error at byte " << ex.byte << std::endl;
                std::cerr << ex.what() << std::endl;
            }

            this->client_id = j["id"];
            LOG("Client id: ", this->client_id);

            state = NetworkClientState::NCS_SayingHello;

            // receive game state
            while (true)
            {
                try
                {
                    zmq::message_t msg;
                    sub.recv(&msg);
                    char *data = (char *)msg.data();
                    if (msg.size() == 0)
                        continue;

                    enum PacketType type = (enum PacketType)data[0];

                    std::string ss(data + 1, msg.size() - 1);
                    json j = json::parse(ss);

                    switch (type)
                    {
                    case PacketType::PT_WORLDSTATE:
                        handleGameState(j);
                        break;

                    default:
                        break;
                    }
                }
                catch (const zmq::error_t &e)
                {
                    std::cerr << e.what() << '\n';
                }
                catch (const json::parse_error &ex)
                {
                    std::cerr << "parse error at byte " << ex.byte << std::endl;
                    std::cerr << ex.what() << std::endl;
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << '\n';
                }
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

GameClient::GameClient() : context(1), req(context, zmq::socket_type::req)
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
    GameEngine::LOG("GameClient::run() exit");
}

void GameClient::set_connect_to_server(bool is_connnect_to_server)
{
    this->is_connnect_to_server = is_connnect_to_server;
}

void GameClient::handleGameState(json j)
{
    // Lock all game state
    // LOG("handleGameState at", j["frame"].get<int>());
    // Got world state time
    json objs = j["objects"];
    GameObjectManager::Get().fromJSON(objs);
}

} // namespace GameEngine
