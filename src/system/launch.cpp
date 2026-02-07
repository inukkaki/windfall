#include "system/launch.h"

#include <cstdint>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "system/config.h"
#include "system/modal.h"

namespace windfall::system::launch {

namespace impl {

namespace config = windfall::system::config;
namespace modal = windfall::system::modal;

}  // namespace impl

namespace {

bool InitSdl(uint32_t flags)
{
    bool succeeds = true;
    if (SDL_Init(flags) < 0) {
        succeeds = false;
        impl::modal::ShowErrorMessage(
            "Initialization Error",
            "Could not initialize SDL.",
            SDL_GetError());
    }
    return succeeds;
}

bool CreateWindow(SDL_Window*& window)
{
    bool succeeds = true;
    int window_width = impl::config::GetWindowWidth();
    int window_height = impl::config::GetWindowHeight();
    window = SDL_CreateWindow(
        impl::config::kTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        window_width, window_height, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        succeeds = false;
        impl::modal::ShowErrorMessage(
            "Initialization Error",
            "Could not create a main window.",
            SDL_GetError());
    }
    return succeeds;
}

bool CreateRenderer(SDL_Window* window, SDL_Renderer*& renderer)
{
    bool succeeds = true;
    renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        succeeds = false;
        impl::modal::ShowErrorMessage(
            "Initialization Error",
            "Could not create a renderer.",
            SDL_GetError());
    } else {
        float window_scale = impl::config::GetWindowScale();
        SDL_RenderSetScale(renderer, window_scale, window_scale);
    }
    return succeeds;
}

bool InitSdlImage(int flags)
{
    bool succeeds = true;
    if (!(IMG_Init(flags) | flags)) {
        succeeds = false;
        impl::modal::ShowErrorMessage(
            "Initialization Error",
            "Could not initialize SDL_image.",
            IMG_GetError());
    }
    return succeeds;
}

}  // namespace

bool InitGui(SDL_Window*& window, SDL_Renderer*& renderer)
{
    bool succeeds = false;
    if (InitSdl(SDL_INIT_VIDEO)) {
        if (CreateWindow(window) && CreateRenderer(window, renderer)) {
            if (InitSdlImage(IMG_INIT_PNG)) {
                succeeds = true;
            }
        }
    }
    return succeeds;
}

void CloseGui(SDL_Window*& window, SDL_Renderer*& renderer)
{
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    SDL_DestroyWindow(window);
    window = nullptr;
    SDL_Quit();
}

}  // namespace windfall::system::launch
