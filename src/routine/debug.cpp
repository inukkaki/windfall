#include "routine/debug.h"

#include <iostream>

#include "SDL2/SDL.h"

#include "interface/keyboard.h"
#include "routine/event.h"
#include "system/config.h"
#include "time/framerate.h"

namespace windfall::routine::debug {

namespace impl {

namespace kbd = windfall::interface::keyboard;
namespace revent = windfall::routine::event;
namespace config = windfall::system::config;
namespace framerate = windfall::time::framerate;

}  // namespace impl

void DebugRoutine(SDL_Window* window, SDL_Renderer* renderer)
{
    // Keyboard
    impl::kbd::Keyboard kbd;

    // Frame rate
    impl::framerate::FrameRateAdjuster fra(impl::config::GetFrameRate());
    impl::framerate::FrameRateMeasurer frm;
    double measured_frame_rate = 0.0;

    // Main loop
    bool quits = false;
    while (!quits) {
        // Handle events
        quits = impl::revent::HandleEvents(kbd);

        // DEBUG
        if (kbd.Presses(impl::kbd::KeyCode::kLeft)) {
            std::cout << "L" << std::endl;
        }
        if (kbd.Pressing(impl::kbd::KeyCode::kRight)) {
            std::cout << "R" << std::endl;
        }
        if (kbd.Releases(impl::kbd::KeyCode::kDown)) {
            std::cout << "D" << std::endl;
        }

        // Keyboard
        kbd.Update();

        // Frame rate
        if (frm.MeasureFrameRate(measured_frame_rate)) {
            std::cout << measured_frame_rate << " fps" << std::endl;
        }
        fra.Adjust();
    }
}

}  // namespace windfall::routine::debug
