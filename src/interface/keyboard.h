#ifndef WINDFALL_INTERFACE_KEYBOARD_H_
#define WINDFALL_INTERFACE_KEYBOARD_H_

#include <array>
#include <unordered_map>

#include "SDL2/SDL.h"

namespace windfall::interface::keyboard {

enum class KeyCode : unsigned char {
    kW,
    kA,
    kS,
    kD,
    kUp,
    kLeft,
    kRight,
    kDown,
    kMax,
};

struct Key {
    bool curr;  // Represents if this key is pressed in the current frame
    bool prev;  // Represents if this key was pressed in the previous frame

    Key() : curr(false), prev(false) {}
};

namespace impl {

using KeyMap = std::unordered_map<SDL_KeyCode, int>;
using KeyArray = std::array<Key, static_cast<int>(KeyCode::kMax)>;

}  // namespace impl

class Keyboard {
public:
    Keyboard()
    {
        SetKeyMap();
    }

    void SetKeyMap();

    void Clear();

    void HandleKeyDown(SDL_Keycode key);
    void HandleKeyUp(SDL_Keycode key);

    void Update();

    bool Presses(KeyCode key) const;
    bool Pressing(KeyCode key) const;
    bool Releases(KeyCode key) const;

private:
    impl::KeyMap key_map_;
    impl::KeyArray pressed_;
};

}  // namespace windfall::interface::keyboard

#endif  // WINDFALL_INTERFACE_KEYBOARD_H_
