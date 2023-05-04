#pragma once
#include <cstdint>

namespace GameEngine
{

const int cycles_per_second = 60;

class Clock
{
  public:
    int64_t time_cycles;
    float time_scale;
    bool is_paused;

    static inline int64_t secondsToCycle(float seconds)
    {
        return seconds * cycles_per_second;
    }

    static inline float cycleToSeconds(int64_t cycles)
    {
        return cycles / cycles_per_second;
    }

    explicit Clock(float startTime = 0.f) : time_cycles(0), time_scale(1.0f), is_paused(false)
    {
    }

    float calcDelta(const Clock &other) const
    {
        return cycleToSeconds(time_cycles - other.time_cycles);
    }

    void update(float dtReadSeconds)
    {
        if (!is_paused)
        {
            time_cycles += (int64_t)secondsToCycle(dtReadSeconds * time_scale);
        }
    }
};

class Timeline
{
    std::chrono::high_resolution_clock::time_point last_time;
    Clock clock;

  public:
    Timeline(float startTime = 0.f) : clock(startTime)
    {
    }

    inline float getLastDeltaTime() const
    {
        return Clock::cycleToSeconds(clock.time_cycles);
    }

    inline void addNewKeyFrame()
    {
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> dt = now - last_time;
        last_time = now;
        clock.update(dt.count());
    }

    inline void reset()
    {
        last_time = std::chrono::high_resolution_clock::now();
        clock = Clock();
    }

    inline void pause()
    {
        clock.is_paused = true;
    }
};

} // namespace GameEngine
