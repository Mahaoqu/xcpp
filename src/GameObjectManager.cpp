#include "GameObjectManager.h"
#include "GameObjectRegistry.h"

namespace GameEngine
{

void GameObjectManager::add(GameObject *gameObject)
{
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
    for (auto gameObject : gameObjects)
    {
        delete gameObject;
    }
    gameObjects.clear();
    for (auto gameObjectJSON : j)
    {
        // Find the class of the object
        GameObject *gameObject = GameObjectRegistry::Get().CreateGameObject(gameObjectJSON["classId"]);
        gameObject->fromJSON(gameObjectJSON);
        gameObjects.push_back(gameObject);
    }
}

} // namespace GameEngine