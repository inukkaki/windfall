#include "SDL2/SDL.h"

#include "system/launch.h"

#if (defined(__WIN32) || defined(__WIN64))
    #include "system/winfunc.h"
#endif

// DEBUG
#include "system/modal.h"
#include "time/timer.h"
#include "time/framerate.h"
#include "system/config.h"
#include <iostream>

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
        windfall::time::timer::SimpleTimer timer;
        timer.Set();
        //windfall::system::config::SetFrameRate(30);
        windfall::time::framerate::FrameRateAdjuster fra(
            windfall::system::config::GetFrameRate());
        windfall::time::framerate::FrameRateMeasurer frm;
        double measured_frame_rate = 0.0;
        while (timer.GetElapsedTime() < 5000) {
            if (frm.MeasureFrameRate(measured_frame_rate)) {
                std::cout << measured_frame_rate << " fps" << std::endl;
            }
            fra.Adjust();
        }
        windfall::system::modal::ShowErrorMessage("main", "succeeded in init");
    }

    impl::launch::CloseGui(window, renderer);

    return 0;
}
