#include "Common.h"
#include "Event.h"

enum EventType
{
    EVENT_TYPE_COLLIDE,
    EVENT_TYPE_PLAYER_DEAD,
    EVENT_TYPE_PLAYER_RESPAWN,
    EVENT_TYPE_PLAYER_INPUT,

    EVENT_TYPE_RECORD,
    EVENT_TYPE_RECORD_END,
    EVENT_TYPE_RECORD_REPLAY
};

class EventCollide : public GameEngine::Event
{
    int id1;
    int id2;
    EventCollide(int id1, int id2) : id1(id1), id2(id2)
    {
    }
};

class EventPlayerDead : public GameEngine::Event
{
    int id;
    EventPlayerDead(int id) : id(id)
    {
    }
};

class EventPlayerRespawn : public GameEngine::Event
{
};

class EventPlayerInput : public GameEngine::Event
{
  public:
    int id;
    int key;
    bool pressed;

    EventPlayerInput(int id, int key, bool pressed) : id(id), key(key), pressed(pressed)
    {
    }
};

class EventRecord : public GameEngine::Event
{
    EventRecord() = default;
};

class EventRecordEnd : public GameEngine::Event
{
};
