#ifndef WINDFALL_SYSTEM_LAUNCH_H_
#define WINDFALL_SYSTEM_LAUNCH_H_

#include "SDL2/SDL.h"

namespace windfall::system::launch {

bool InitGui(SDL_Window*& window, SDL_Renderer*& renderer);
void CloseGui(SDL_Window*& window, SDL_Renderer*& renderer);

}  // namespace windfall::system::launch

#endif  // WINDFALL_SYSTEM_LAUNCH_H_
