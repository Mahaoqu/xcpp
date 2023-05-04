#pragma once

#include "Common.h"
#include "Timeline.h"
#include <v8.h>

#define GO_DEBUG 0

#define CLASS_IDENTIFICATION(inCode, inClass)                                                                          \
    enum                                                                                                               \
    {                                                                                                                  \
        kClassId = inCode                                                                                              \
    };                                                                                                                 \
    virtual uint32_t GetClassId() const                                                                                \
    {                                                                                                                  \
        return kClassId;                                                                                               \
    }                                                                                                                  \
    static GameObject *CreateInstance()                                                                                \
    {                                                                                                                  \
        return new inClass();                                                                                          \
    }

namespace GameEngine
{
/**
 * Simple class to demonstrate Interceptors, Accessors, Handles, and object
 * creation in v8
 *
 * NOTE: I've used GameObject to help you think about the functionality as it
 * relates to scripting, but this could be any kind of objet (i.e., Events)..
 */

class Event;

class GameObject
{
  public:
    GameObject();
    virtual ~GameObject();

    CLASS_IDENTIFICATION('GOBJ', GameObject)

    std::string guid;
    int x;
    int y;

    bool isCollidable;

    /**
     * This function will make this class instance accessible to scripts in
     * the given context.
     *
     * IMPORTANT: Please read this definition of this function in
     * GameObject.cpp. The helper function I've provided expects certain
     * parameters which you must use in order to take advance of this
     * convinience.
     */
    v8::Local<v8::Object> exposeToV8(v8::Isolate *isolate, v8::Local<v8::Context> &context,
                                     std::string context_name = "default");

    /**
     * Static function to keep track of current total number of
     * gameobjects, to facilitate creating GUIDs by incrementing a counter.
     */
    static int getCurrentGUID();

    /**
     * Shared list of all instances of game objects...auto populated by the
     * constructor.
     */
    static std::vector<GameObject *> game_objects;

    /**
     * Factor methods for creating new instances of GameObjects.
     *
     * This is primarily a demonstration of how you can create new objects
     * in javascript. NOTE: this is embedded in this GameObject class, but
     * could (and likely should) be used for other functionality as well
     * (i.e., Events).
     */
    static GameObject *GameObjectFactory(std::string context_name = "default");
    static void ScriptedGameObjectFactory(const v8::FunctionCallbackInfo<v8::Value> &args);

    /**
     * Render interface for GameObjects.
     * Into SFML window.
     */
    bool renderable = false;
    virtual void render(sf::RenderWindow &window)
    {
    }

    /**
     *  Update interface for GameObjects. Connects to Timeline.
     */
    virtual void update(const Timeline &timeline)
    {
    }

    /**
     *  Handle events interface for GameObjects. Default do nothing.
     */
    virtual bool onEvent(const Event &event)
    {
        return true;
    }

    virtual bool isColliding(const GameObject &other)
    {
        return false;
    }

    /**
     * Serialize interface for GameObjects.
     */
    virtual json toJSON()
    {
        json j;
        j["type"] = kClassId; // For initialization
        j["guid"] = guid;
        j["x"] = x;
        j["y"] = y;
        j["isCollidable"] = isCollidable;
        return j;
    }

    /**
     * Deserialize interface for GameObjects.
     */
    virtual void fromJSON(json j)
    {
        guid = j["guid"];
        x = j["x"];
        y = j["y"];
        isCollidable = j["isCollidable"];
    }

  private:
    /** Static variable to keep count of current number of GameObject instances */
    static int current_guid;

    v8::Isolate *isolate;
    v8::Global<v8::Context> *context;

    /**
     * NOTE: These "Accessors" have to be **static**
     *
     * You will need to implement a setter and getter for every class
     * member variable you want accessible to javascript.
     */
    static void setGameObjectX(v8::Local<v8::String> property, v8::Local<v8::Value> value,
                               const v8::PropertyCallbackInfo<void> &info);
    static void getGameObjectX(v8::Local<v8::String> property,
                               const v8::PropertyCallbackInfo<v8::Value> &info); // note return type
    static void setGameObjectY(v8::Local<v8::String> property, v8::Local<v8::Value> value,
                               const v8::PropertyCallbackInfo<void> &info);
    static void getGameObjectY(v8::Local<v8::String> property,
                               const v8::PropertyCallbackInfo<v8::Value> &info); // note return type
    static void setGameObjectGUID(v8::Local<v8::String> property, v8::Local<v8::Value> value,
                                  const v8::PropertyCallbackInfo<void> &info);
    static void getGameObjectGUID(v8::Local<v8::String> property,
                                  const v8::PropertyCallbackInfo<v8::Value> &info); // note return type
};

} // namespace GameEngine