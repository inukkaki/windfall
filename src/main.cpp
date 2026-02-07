#include "SDL2/SDL.h"

#include "system/launch.h"

// DEBUG
#include "system/modal.h"
#include "system/assert.h"

namespace impl {

namespace launch = windfall::system::launch;

}  // namespace impl

int main(int argc, char* argv[])
{
    // DEBUG
    //INUK_ASSERT(0 == 1);

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
