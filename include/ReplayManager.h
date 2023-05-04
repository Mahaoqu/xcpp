#pragma once

#include "Common.h"
#include "Event.h"
#include "Timeline.h"

namespace GameEngine
{

/**
 * ReplayManager only runs on the client.
 *
 */
class ReplayManager
{
  private:
    Timeline *timeline;

    bool is_recording, is_playing;
    double start_time;

    // On one time frame, we need to record the logic dependencies of all the events.
    std::priority_queue<Event *, std::vector<Event *>> happened_before;

  public:
    static ReplayManager &Get()
    {
        static ReplayManager sInstance;
        return sInstance;
    }

    ReplayManager(/* args */);
    ~ReplayManager();

    void startRecording();
    void endRecording();
    void startReplaying();
    void endReplaying();
    void resetPlaySpeed(double speed);
};

} // namespace GameEngine