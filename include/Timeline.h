#pragma once
#include <cstdint>

namespace GameEngine
{

const int cycles_per_second = 60;
const int fps = cycles_per_second;

class Timeline
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

    explicit Timeline(float startTime = 0.f) : time_cycles(0), time_scale(1.0f), is_paused(false)
    {
    }

    float calcDelta(const Timeline &other) const
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

} // namespace GameEngine