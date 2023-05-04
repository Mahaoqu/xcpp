#pragma once

#include "Common.h"
#include "GameObject.h"

namespace GameEngine
{
class GameClient
{
  private:
    std::string game_title_name = "game";
    sf::RenderWindow window;
    Timeline tl;

    void render();
    void handleInput();

    // config
    int width = 800;
    int height = 600;

    // network
    const int port = 5555;
    bool is_connnect_to_server = false;
    std::string server_addr;

    std::set<sf::Keyboard::Key> pressed_keys;

    void newFrame();
    void handleKeyPress(sf::Keyboard::Key key);
    void handleKeyRelease(sf::Keyboard::Key key);

  public:
    GameClient(/* args */);
    ~GameClient();

    void init();
    void run();

    void addToScene(GameObject *obj);
    void removeFromScene(GameObject *obj);
};

} // namespace GameEngine
