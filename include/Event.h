#pragma once

#include "Common.h"
#include "GameObject.h"

namespace GameEngine
{

class Event
{
  private:
    int event_type_id; // Defined by yourself
    double time;       // Time of event

  public:
    Event() = default;
    ~Event() = default; // Must be trivially destructible
};

} // namespace GameEngine
