#ifndef WINDFALL_TIME_TIMER_H_
#define WINDFALL_TIME_TIMER_H_

#include <cstdint>

namespace windfall::time::timer {

class SimpleTimer {
public:
    SimpleTimer()
    {
        Set();
    }

    void Set();
    uint64_t GetElapsedTime() const;

private:
    uint64_t start_time_;
};

}  // namespace windfall::time::timer

#endif  // WINDFALL_TIME_TIMER_H_
