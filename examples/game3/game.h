#include "Common.h"
#include "GameObject.h"
#include "GameObjectManager.h"
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

    virtual void fromJSON(json j) override
    {
        GameObject::fromJSON(j);
        width = j["width"].get<int>();
        height = j["height"].get<int>();
        color = sf::Color(j["color"]["r"].get<int>(), j["color"]["g"].get<int>(), j["color"]["b"].get<int>());
    }
    virtual json toJSON() override
    {
        json j = GameObject::toJSON();
        j["type"] = kClassId;
        j["width"] = width;
        j["height"] = height;
        j["color"]["r"] = color.r;
        j["color"]["g"] = color.g;
        j["color"]["b"] = color.b;
        return j;
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

    virtual void fromJSON(json j) override
    {
        RecObject::fromJSON(j);
        velocity.x = j["velocity"]["x"].get<float>();
        velocity.y = j["velocity"]["y"].get<float>();
    }
    virtual json toJSON() override
    {
        json j = RecObject::toJSON();
        j["type"] = kClassId;
        j["velocity"]["x"] = velocity.x;
        j["velocity"]["y"] = velocity.y;
        return j;
    }
    virtual void update(const Timeline &tl) override;
};

class Character : public MovingObject
{
  public:
    CLASS_IDENTIFICATION('CHAR', Character)

    int client_id = 0;
    bool onJumping = false;
    bool onGround = false;

    sf::Vector2f acceleration;

    Character() : MovingObject()
    {
        width = 10;
        height = 10;
        color = sf::Color::Blue;
    }

    Character(int client_id) : Character()
    {
        this->client_id = client_id;
    }

    ~Character()
    {
    }

    void jump()
    {
    }

    virtual void fromJSON(json j) override
    {
        MovingObject::fromJSON(j);
        client_id = j["client_id"].get<int>();
        onJumping = j["onJumping"].get<bool>();
        onGround = j["onGround"].get<bool>();
        acceleration.x = j["acceleration"]["x"].get<float>();
        acceleration.y = j["acceleration"]["y"].get<float>();
    }
    virtual json toJSON() override
    {
        json j = MovingObject::toJSON();
        j["type"] = kClassId;
        j["client_id"] = client_id;
        j["onJumping"] = onJumping;
        j["onGround"] = onGround;
        j["acceleration"]["x"] = acceleration.x;
        j["acceleration"]["y"] = acceleration.y;
        return j;
    }

    // virtual void render(sf::RenderWindow &window) override;
    virtual void update(const Timeline &) override;
};

// Called by server/client to register game object classes
inline void RegisterGameObjectClasses()
{
    GameObjectRegistry::Get().registerGameObject<GameObject>();
    GameObjectRegistry::Get().registerGameObject<RecObject>();
    GameObjectRegistry::Get().registerGameObject<MovingObject>();
    GameObjectRegistry::Get().registerGameObject<Character>();
}
