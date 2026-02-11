#include "interface/keyboard.h"

#include <unordered_map>

#include "SDL2/SDL.h"

namespace windfall::interface::keyboard {

void Keyboard::SetKeyMap()
{
    key_map_.clear();
    std::unordered_map<SDL_KeyCode, KeyCode> code_pairs = {
        {SDLK_UP,    KeyCode::kUp},
        {SDLK_LEFT,  KeyCode::kLeft},
        {SDLK_RIGHT, KeyCode::kRight},
        {SDLK_DOWN,  KeyCode::kDown},
    };
    for (const auto& [key, value] : code_pairs) {
        key_map_.insert({key, static_cast<int>(value)});
    }
}

void Keyboard::Clear()
{
    for (auto& pressed : pressed_) {
        pressed.curr = false;
        pressed.prev = false;
    }
}

void Keyboard::HandleKeyDown(SDL_Keycode key)
{
    auto it = key_map_.find(static_cast<SDL_KeyCode>(key));
    if (it != key_map_.end()) {
        int index = it->second;
        pressed_[index].curr = true;
    }
}

void Keyboard::HandleKeyUp(SDL_Keycode key)
{
    auto it = key_map_.find(static_cast<SDL_KeyCode>(key));
    if (it != key_map_.end()) {
        int index = it->second;
        pressed_[index].curr = false;
    }
}

void Keyboard::Update()
{
    for (auto& pressed : pressed_) {
        pressed.prev = pressed.curr;
    }
}

bool Keyboard::Presses(KeyCode key) const
{
    const auto& pressed = pressed_.at(static_cast<int>(key));
    return pressed.curr && !pressed.prev;
}

bool Keyboard::Pressing(KeyCode key) const
{
    const auto& pressed = pressed_.at(static_cast<int>(key));
    return pressed.curr;
}

bool Keyboard::Releases(KeyCode key) const
{
    const auto& pressed = pressed_.at(static_cast<int>(key));
    return !pressed.curr && pressed.prev;
}

}  // namespace windfall::interface::keyboard
