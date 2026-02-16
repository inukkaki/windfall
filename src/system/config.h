#ifndef WINDFALL_SYSTEM_CONFIG_H_
#define WINDFALL_SYSTEM_CONFIG_H_

namespace windfall::system::config {

inline constexpr char kTitle[] = "windfall";

inline constexpr float kDefaultWindowScale = 2.0f;

inline constexpr int kWindowBaseWidth = 480;
inline constexpr int kWindowBaseHeight = 360;

inline constexpr int kDefaultFrameRate = 60;  // s-1

float GetWindowScale();
void SetWindowScale(float window_scale);

int GetWindowWidth();
int GetWindowHeight();

int GetFrameRate();
void SetFrameRate(int frame_rate);

float GetFrameDuration();

inline constexpr float kZeroTolerance = 1e-6f;

bool EqualsZero(float x);

}  // namespace windfall::system::config

#endif  // WINDFALL_SYSTEM_CONFIG_H_
