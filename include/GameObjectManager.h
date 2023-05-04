#pragma once

#include "Common.h"
#include "GameObject.h"

namespace GameEngine
{

enum ReplicationAction
{
    RA_Create,
    RA_Update,
    RA_Destroy,
    RA_MAX,
};

// Singleton to manage all game
class GameObjectManager
{
  private:
    std::list<GameObject *> gameObjects;

  public:
    static GameObjectManager &Get()
    {
        static GameObjectManager sInstance;
        return sInstance;
    }

    GameObjectManager() = default;
    ~GameObjectManager() = default;

    std::list<GameObject *> &getObjects()
    {
        return gameObjects;
    }
    void add(GameObject *gameObject);
    json toJSON();
    void fromJSON(json j);
};

} // namespace GameEngine
