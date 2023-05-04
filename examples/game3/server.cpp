#include "GameServer.h"
#include "game.h"

const int width = 800;
const int height = 600;

std::vector<GameObject *> initScene()
{
    std::vector<GameObject *> scene;

    RecObject *bg = new RecObject();
    bg->width = width;
    bg->height = height / 4;
    bg->x = 0;
    bg->y = height - bg->height;
    bg->color = sf::Color::White;
    scene.push_back(bg);

    return scene;
}

class MyGameServer : public GameEngine::GameServer
{
    const int max_clients = 100;
    std::set<int> clients;
    int next_client_id = 0;

    void beforeServerStart() override
    {
        auto scene = initScene();
        GameEngine::LOG("Scene inited ", scene.size(), " objects");
    }

    json onNewClient(json nc) override
    {
        GameEngine::LOG("New client connected");
        // allocate a new number
        int client_id = next_client_id;

        // reset next to the lowest number
        clients.insert(client_id);
        for (next_client_id = 0; next_client_id < 100; next_client_id++)
        {
            if (clients.find(next_client_id) == clients.end())
            {
                break;
            }
            next_client_id++;
        }

        // Create new player object
        Character *p = new Character(client_id);
        p->x = 100;

        json j;
        j["id"] = client_id;
        return j;
    }

    json onClientInput(json input) override
    {

        return json();
    }

    json onClientDisconnected(json dis) override
    {
        // Remove player object

        return json();
    }
};

int main(int argc, char const *argv[])
{
    MyGameServer server;

    server.run();
    return 0;
}
