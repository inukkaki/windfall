#include "routine/event.h"

#include "SDL2/SDL.h"

#include "interface/keyboard.h"
#include "interface/mouse.h"

namespace windfall::routine::event {

namespace impl {

namespace kbd = windfall::interface::keyboard;
namespace mouse = windfall::interface::mouse;

}  // namespace impl

bool HandleEvents(impl::kbd::Keyboard& kbd, impl::mouse::Mouse& mouse)
{
    bool quits = false;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            quits = true;
            break;
        case SDL_KEYDOWN:
            kbd.HandleKeyDown(event.key.keysym.sym);
            break;
        case SDL_KEYUP:
            kbd.HandleKeyUp(event.key.keysym.sym);
            break;
        case SDL_MOUSEBUTTONDOWN:
            mouse.HandleButtonDown(event.button.button);
            break;
        case SDL_MOUSEBUTTONUP:
            mouse.HandleButtonUp(event.button.button);
            break;
        case SDL_MOUSEMOTION:
            mouse.HandleMotion(
                event.motion.x, event.motion.y,
                event.motion.xrel, event.motion.yrel);
            break;
        case SDL_MOUSEWHEEL:
            mouse.HandleWheel(event.wheel.y);
            break;
        default:
            break;
        }
    }
    return quits;
}

}  // namespace windfall::routine::event
