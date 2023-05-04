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

    template <typename T> void RegisterGameObject()
    {
        assert(mNameToGameObjectCreationFunctionMap.find(T::kClassId) == mNameToGameObjectCreationFunctionMap.end());
        mNameToGameObjectCreationFunctionMap[T::kClassId] = &T::CreateInstance;
    }

    GameObject *CreateGameObject(uint32_t inClassId)
    {
        // add error checking if desired- for now crash if not found
        GameObjectCreationFunc creationFunc = mNameToGameObjectCreationFunctionMap[inClassId];
        GameObject *gameObject = creationFunc();
        return gameObject;
    }

  private:
    GameObjectRegistry() = default;
    std::unordered_map<uint32_t, GameObjectCreationFunc> mNameToGameObjectCreationFunctionMap;
};

} // namespace GameEngine
