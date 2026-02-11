#include "routine/event.h"

#include "SDL2/SDL.h"

#include "interface/keyboard.h"

namespace windfall::routine::event {

namespace impl {

namespace kbd = windfall::interface::keyboard;

}  // namespace impl

bool HandleEvents(impl::kbd::Keyboard& kbd)
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
        default:
            break;
        }
    }
    return quits;
}

}  // namespace windfall::routine::event
