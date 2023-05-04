#pragma once

#include "Common.h"
#include "GameObject.h"

namespace GameEngine
{

typedef GameObject *(*GameObjectCreationFunc)();

/**
 * Use singleton to create new object by class id
 */
class GameObjectRegistry
{
  public:
    static GameObjectRegistry &Get()
    {
        static GameObjectRegistry sInstance;
        return sInstance;
    }

    template <typename T> void registerGameObject()
    {
        assert(mNameToGameObjectCreationFunctionMap.find(T::kClassId) == mNameToGameObjectCreationFunctionMap.end());
        mNameToGameObjectCreationFunctionMap[T::kClassId] = &T::CreateInstance;
        LOG("GameObjectRegistry::registerGameObject: ", T::kClassId);
    }

    GameObject *createGameObject(uint32_t inClassId)
    {
        // add error checking if desired- for now crash if not found
        GameObjectCreationFunc creationFunc = mNameToGameObjectCreationFunctionMap[inClassId];
        if (creationFunc == nullptr)
        {
            std::cerr << "GameObjectRegistry::createGameObject failed to find class id: " << inClassId << std::endl;
            return nullptr;
        }
        GameObject *gameObject = creationFunc();
        return gameObject;
    }

  private:
    GameObjectRegistry() = default;
    std::unordered_map<uint32_t, GameObjectCreationFunc> mNameToGameObjectCreationFunctionMap;
};

} // namespace GameEngine
