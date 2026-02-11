#include "time/framerate.h"

#include <cstdint>
#include <limits>

#include "SDL2/SDL.h"

#include "system/assert.h"

namespace windfall::time::framerate {

void FrameRateAdjuster::SetFrameRate(int frame_rate)
{
    INUK_ASSERT(frame_rate > 0);
    frame_rate_ = frame_rate;
    frame_duration_ = 1000.0/frame_rate_;
}

void FrameRateAdjuster::SetTimer()
{
    timer_.Set();
}

void FrameRateAdjuster::Delay() const
{
    uint64_t elapsed_time = timer_.GetElapsedTime();
    double delay_time = frame_duration_ - 1.0*elapsed_time;
    if (delay_time > 0.0) {
        SDL_Delay(
            delay_time < std::numeric_limits<uint32_t>::max()
                ? static_cast<uint32_t>(delay_time)
                : std::numeric_limits<uint32_t>::max());
    }
}

void FrameRateAdjuster::Adjust()
{
    Delay();
    SetTimer();
}

}  // namespace windfall::time::framerate
