#include "system/config.h"

#include "system/assert.h"

namespace windfall::system::config {

namespace {

float gWindowScale = kDefaultWindowScale;

int gWindowWidth = static_cast<int>(kWindowBaseWidth*gWindowScale);
int gWindowHeight = static_cast<int>(kWindowBaseHeight*gWindowScale);

int gFrameRate = kDefaultFrameRate;  // s-1

}  // namespace

float GetWindowScale()
{
    return gWindowScale;
}

void SetWindowScale(float window_scale)
{
    INUK_ASSERT(window_scale > 0.0f);
    gWindowScale = window_scale;
    gWindowWidth = static_cast<int>(kWindowBaseWidth*gWindowScale);
    gWindowHeight = static_cast<int>(kWindowBaseHeight*gWindowScale);
}

int GetWindowWidth()
{
    return gWindowWidth;
}

int GetWindowHeight()
{
    return gWindowHeight;
}

int GetFrameRate()
{
    return gFrameRate;
}

void SetFrameRate(int frame_rate)
{
    INUK_ASSERT(frame_rate > 0);
    gFrameRate = frame_rate;
}

}  // namespace windfall::system::config
