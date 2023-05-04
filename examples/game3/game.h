#include "Common.h"
#include "GameObject.h"

#include <iostream>

using namespace GameEngine;

class RecObject : public GameObject
{
  public:
    int width;
    int height;
    bool collidable = false;

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

    void updateByInput();

    virtual void render(sf::RenderWindow &window) override;
    virtual void update(const Timeline &) override;
};
