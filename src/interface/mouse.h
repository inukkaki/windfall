#ifndef WINDFALL_INTERFACE_MOUSE_H_
#define WINDFALL_INTERFACE_MOUSE_H_

#include <array>
#include <cstdint>
#include <unordered_map>

namespace windfall::interface::mouse {

enum class ButtonCode : unsigned char {
    kLeft,
    kMiddle,
    kRight,
    kMax,
};

struct Button {
    bool curr;  // Represents if this button is pressed in the current frame
    bool prev;  // Represents if this button was pressed in the previous frame

    Button() : curr(false), prev(false) {}
};

namespace impl {

using ButtonMap = std::unordered_map<uint8_t, int>;
using ButtonArray = std::array<Button, static_cast<int>(ButtonCode::kMax)>;

}  // namespace impl

class Mouse {
public:
    Mouse() : x_(0), y_(0), dx_(0), dy_(0), scrolls_(0)
    {
        SetButtonMap();
    }

    int x() const { return x_; }
    int y() const { return y_; }
    int dx() const { return dx_; }
    int dy() const { return dy_; }

    int scrolls() const { return scrolls_; }

    void SetButtonMap();

    void Clear();

    void HandleButtonDown(uint8_t button_index);
    void HandleButtonUp(uint8_t button_index);
    void HandleMotion(int32_t x, int32_t y, int32_t dx, int32_t dy);
    void HandleWheel(int32_t scrolls);

    void Update();

    bool Presses(ButtonCode button) const;
    bool Pressing(ButtonCode button) const;
    bool Releases(ButtonCode button) const;

private:
    impl::ButtonMap button_map_;
    impl::ButtonArray pressed_;

    int x_;
    int y_;
    int dx_;
    int dy_;

    int scrolls_;
};

}  // namespace windfall::interface::mouse

#endif  // WINDFALL_INTERFACE_MOUSE_H_
