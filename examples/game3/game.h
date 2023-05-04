#include "Common.h"
#include "GameObject.h"
#include "GameObjectRegistry.h"

#include <iostream>

using namespace GameEngine;

class RecObject : public GameObject
{
  public:
    CLASS_IDENTIFICATION('ROBJ', RecObject)

    int width;
    int height;
    sf::Color color;

    RecObject() : GameObject()
    {
        width = 0;
        height = 0;
    }

    ~RecObject()
    {
    }

    virtual void render(sf::RenderWindow &window) override;
    // virtual void update(const Timeline &tl);
};

class MovingObject : public RecObject
{
  public:
    CLASS_IDENTIFICATION('MOBJ', MovingObject)

    sf::Vector2f velocity;
    MovingObject() : RecObject()
    {
    }

    ~MovingObject()
    {
    }

    virtual void update(const Timeline &tl) override;
};

class Character : public MovingObject
{
  public:
    CLASS_IDENTIFICATION('CHAR', Character)

    bool onJumping = false;
    bool onGround = false;

    sf::Vector2f acceleration;

    Character() : MovingObject()
    {
        width = 10;
        height = 10;
        color = sf::Color::Blue;
    }

    ~Character()
    {
    }

    void jump()
    {
    }

    virtual void render(sf::RenderWindow &window) override;
    virtual void update(const Timeline &) override;
};

// Called by server/client to register game object classes
inline void RegisterGameObjectClasses()
{
    GameObjectRegistry::Get().RegisterGameObject<RecObject>();
    GameObjectRegistry::Get().RegisterGameObject<MovingObject>();
    GameObjectRegistry::Get().RegisterGameObject<Character>();
}
