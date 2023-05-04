#include "GameObjectManager.h"
#include "GameObjectRegistry.h"

namespace GameEngine
{

void GameObjectManager::add(GameObject *gameObject)
{
    // std::lock_guard<std::mutex> lock(mutex);
    gameObjects.push_back(gameObject);
}

json GameObjectManager::toJSON()
{
    json j;
    for (auto gameObject : gameObjects)
    {
        j.push_back(gameObject->toJSON());
    }
    return j;
}

void GameObjectManager::fromJSON(json j)
{
    // LOG("Update Game State from json");
    std::lock_guard<std::mutex> lock(mutex);

    for (auto gameObjectJSON : j)
    {
        std::string s = gameObjectJSON["guid"];

        GameObject *g = fromGUID(s);
        if (g != nullptr)
        {
            g->fromJSON(gameObjectJSON);
        }
        else
        {
            // Find the class of the object
            uint32_t classId = gameObjectJSON["type"];
            LOG("Add new game object", classId);

            GameObject *gameObject = GameObjectRegistry::Get().createGameObject(classId);
            gameObject->fromJSON(gameObjectJSON);
        }
        // delete unused game object
    }
}

} // namespace GameEngine