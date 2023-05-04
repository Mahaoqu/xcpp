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
    std::mutex mutex;

  public:
    static GameObjectManager &Get()
    {
        static GameObjectManager sInstance;
        return sInstance;
    }

    GameObjectManager() = default;
    ~GameObjectManager() = default;

    void forEach(std::function<void(GameObject *)> func)
    {
        std::lock_guard<std::mutex> lock(mutex);
        for (auto &&obj : gameObjects)
        {
            func(obj);
        }
    }

    GameObject *fromGUID(std::string guid)
    {
        for (auto &&obj : gameObjects)
        {
            if (obj->guid == guid)
                return obj;
        }
        return nullptr;
    }

    std::vector<GameObject *> fromKlassType(uint32_t klassID)
    {
        std::vector<GameObject *> objs;
        for (auto &&obj : gameObjects)
        {
            if (obj->GetClassId() == klassID)
                objs.push_back(obj);
        }
        return objs;
    }

    void add(GameObject *gameObject);
    json toJSON();
    void fromJSON(json j);
};

} // namespace GameEngine
