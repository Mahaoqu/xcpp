#pragma once

#include "Common.h"
#include "GameObject.h"

namespace GameEngine
{

class Event : public GameObject
{
  private:
    /* data */
  public:
    Event(/* args */);
    ~Event();

    static std::list<GameObject *> listener;
};

Event::Event(/* args */)
{
}

Event::~Event()
{
}

} // namespace GameEngine
