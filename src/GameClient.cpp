#include "GameClient.h"

namespace GameEngine
{

void GameClient::render()
{
    window.clear();
    for (auto obj : GameObject::game_objects)
    {
        obj->render(window);
    }

    window.display();
}

void GameClient::handleKeyPress(sf::Keyboard::Key key)
{
    this->pressed_keys.insert(key);
}

void GameClient::handleKeyRelease(sf::Keyboard::Key key)
{
    this->pressed_keys.erase(key);
}

GameClient::GameClient(/* args */)
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
    if (is_connnect_to_server)
    {
        std::thread network_thread;
        network_thread = std::thread([&]() {
            // connect to server

            std::cout << "Connecting to server at " << this->server_addr << std::endl;
            // receive game state
        });

        network_thread.detach();
    }

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
    GameObject::game_objects.push_back(obj);
}

} // namespace GameEngine
