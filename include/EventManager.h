#pragma once

#include "Common.h"
#include "Event.h"

namespace GameEngine
{

/**
 * Both server and client can run event.
 * Run every frame to decouple the game logic.
 *
 * Each game object can register a event.
 * 
 * We can also register an event to raise periodically. 
 */
class EventManager
{
  private:
    std::deque<Event *> queue;

  public:
    EventManager() = default;
    ~EventManager() = default;

    void registerEvent(Event *event);
    void raiseEvent(Event *event);
    void registerEventHandler();
};

} // namespace GameEngine
