#include "Common.h"
#include "Event.h"

enum EventType
{
    EVENT_TYPE_COLLIDE,
    EVENT_TYPE_PLAYER_DEAD,
    EVENT_TYPE_PLAYER_RESPAWN,
    EVENT_TYPE_PLAYER_INPUT,

    EVENT_TYPE_RECORD,
    EVENT_TYPE_RECORD_END
};

class EventCollide : public GameEngine::Event
{
};

class EventPlayerDead : public GameEngine::Event
{
};

class EventPlayerRespawn : public GameEngine::Event
{
};

class EventPlayerInput : public GameEngine::Event
{
};

class EventRecord : public GameEngine::Event
{
    
};

class EventRecordEnd : public GameEngine::Event
{

};
