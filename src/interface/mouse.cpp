#include "interface/mouse.h"

#include <cstdint>
#include <unordered_map>

#include "SDL2/SDL.h"

namespace windfall::interface::mouse {

void Mouse::SetButtonMap()
{
    button_map_.clear();
    std::unordered_map<uint8_t, ButtonCode> code_pairs = {
        {SDL_BUTTON_LEFT,   ButtonCode::kLeft},
        {SDL_BUTTON_MIDDLE, ButtonCode::kMiddle},
        {SDL_BUTTON_RIGHT,  ButtonCode::kRight},
    };
    for (const auto& [key, value] : code_pairs) {
        button_map_.insert({key, static_cast<int>(value)});
    }
}

void Mouse::Clear()
{
    for (auto& pressed : pressed_) {
        pressed.curr = false;
        pressed.prev = false;
    }
    x_ = 0;
    y_ = 0;
    dx_ = 0;
    dy_ = 0;
    scrolls_ = 0;
}

void Mouse::HandleButtonDown(uint8_t button_index)
{
    auto it = button_map_.find(button_index);
    if (it != button_map_.end()) {
        int index = it->second;
        pressed_[index].curr = true;
    }
}

void Mouse::HandleButtonUp(uint8_t button_index)
{
    auto it = button_map_.find(button_index);
    if (it != button_map_.end()) {
        int index = it->second;
        pressed_[index].curr = false;
    }
}

void Mouse::HandleMotion(int32_t x, int32_t y, int32_t dx, int32_t dy)
{
    x_ = static_cast<int>(x);
    y_ = static_cast<int>(y);
    dx_ = static_cast<int>(dx);
    dy_ = static_cast<int>(dy);
}

void Mouse::HandleWheel(int32_t scrolls)
{
    scrolls_ = static_cast<int>(scrolls);
}

void Mouse::Update()
{
    for (auto& pressed : pressed_) {
        pressed.prev = pressed.curr;
    }
    dx_ = 0;
    dy_ = 0;
    scrolls_ = 0;
}

bool Mouse::Presses(ButtonCode button) const
{
    const auto& pressed = pressed_.at(static_cast<int>(button));
    return pressed.curr && !pressed.prev;
}

bool Mouse::Pressing(ButtonCode button) const
{
    const auto& pressed = pressed_.at(static_cast<int>(button));
    return pressed.curr;
}

bool Mouse::Releases(ButtonCode button) const
{
    const auto& pressed = pressed_.at(static_cast<int>(button));
    return !pressed.curr && pressed.prev;
}

}  // namespace windfall::interface::mouse
