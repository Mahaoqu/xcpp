#include "GameClient.h"
#include "game.h"

int width = 800;
int height = 600;

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

    Character *p = new Character();
    p->x = 100;
    p->y = 100;
    scene.push_back(p);

    return scene;
}

int main(int argc, char const *argv[])
{
    GameEngine::GameClient gc;

    auto scene = initScene();

    for (auto &&o : scene)
    {
        gc.addToScene(o);
    }

    gc.init();
    gc.run();
    return 0;
}
