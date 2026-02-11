#ifndef WINDFALL_TIME_FRAMERATE_H_
#define WINDFALL_TIME_FRAMERATE_H_

#include "time/timer.h"

namespace windfall::time::framerate {

namespace impl {

namespace timer = windfall::time::timer;

}  // namespace impl

class FrameRateAdjuster {
public:
    explicit FrameRateAdjuster(int frame_rate)
    {
        SetFrameRate(frame_rate);
        SetTimer();
    }

    void SetFrameRate(int frame_rate);

    void SetTimer();
    void Delay() const;

    void Adjust();

private:
    int frame_rate_;         // s-1
    double frame_duration_;  // ms

    impl::timer::SimpleTimer timer_;
};

}  // namespace windfall::time::framerate

#endif  // WINDFALL_TIME_FRAMERATE_H_
