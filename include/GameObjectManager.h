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

class GameObjectManager
{
  private:
    std::list<GameObject *> gameObjects;

  public:
    GameObjectManager(/* args */);
    ~GameObjectManager();

    void add(GameObject *gameObject);

    void serialize();
    void deserialize();
};

} // namespace GameEngine
