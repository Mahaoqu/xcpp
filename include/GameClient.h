#pragma once

#include "Common.h"
#include "GameObject.h"
#include "NetworkManager.h"

namespace GameEngine
{
class GameClient
{
  private:
    NetworkClientState state = NetworkClientState::NCS_Uninitialized;

    std::string game_title_name = "game";
    sf::RenderWindow window;
    Timeline tl;

    // config
    int width = 800;
    int height = 600;

    // network
    zmq::context_t context;
    zmq::socket_t req;

    const int port = 5555;
    const int publish_port = 5556;
    bool is_connnect_to_server = false;
    std::string server_addr = "localhost";
    int client_id = 0;

    // input, only used when client set to report input each frame
    std::set<sf::Keyboard::Key> pressed_keys;

    void newHandleServerThread();
    void handleKeyPress(sf::Keyboard::Key key);
    void handleKeyRelease(sf::Keyboard::Key key);

    void handleGameState(json j);

    void render();

  public:
    GameClient(/* args */);
    ~GameClient();

    void init();
    void run();

    void set_connect_to_server(bool is_connnect_to_server);
};

} // namespace GameEngine
