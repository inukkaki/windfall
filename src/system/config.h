#ifndef WINDFALL_SYSTEM_CONFIG_H_
#define WINDFALL_SYSTEM_CONFIG_H_

namespace windfall::system::config {

inline constexpr char kTitle[] = "windfall";

inline constexpr float kDefaultWindowScale = 2.0f;

inline constexpr int kWindowBaseWidth = 480;
inline constexpr int kWindowBaseHeight = 360;

float GetWindowScale();
void SetWindowScale(float window_scale);

int GetWindowWidth();
int GetWindowHeight();

}  // namespace windfall::system::config

#endif  // WINDFALL_SYSTEM_CONFIG_H_
