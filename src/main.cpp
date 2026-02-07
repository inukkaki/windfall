#include "SDL2/SDL.h"

#include "system/launch.h"

#if (defined(__WIN32) || defined(__WIN64))
    #include "system/winfunc.h"
#endif

// DEBUG
#include "system/modal.h"

namespace impl {

namespace launch = windfall::system::launch;

}  // namespace impl

int main(int argc, char* argv[])
{
    // Resolve the blurriness of the screen
    #if (defined(__WIN32) || defined(__WIN64))
        windfall::system::winfunc::ResolveBlurriness();
    #endif

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    bool initializes_gui = impl::launch::InitGui(window, renderer);

    if (initializes_gui) {
        // DEBUG
        windfall::system::modal::ShowErrorMessage("main", "succeeded in init");
    }

    impl::launch::CloseGui(window, renderer);

    return 0;
}
