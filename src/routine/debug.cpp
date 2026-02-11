#include "routine/debug.h"

#include <iostream>

#include "SDL2/SDL.h"

#include "interface/keyboard.h"
#include "interface/mouse.h"
#include "routine/event.h"
#include "system/config.h"
#include "time/framerate.h"

namespace windfall::routine::debug {

namespace impl {

namespace kbd = windfall::interface::keyboard;
namespace mouse = windfall::interface::mouse;
namespace revent = windfall::routine::event;
namespace config = windfall::system::config;
namespace framerate = windfall::time::framerate;

}  // namespace impl

void DebugRoutine(SDL_Window* window, SDL_Renderer* renderer)
{
    // Keyboard & mouse
    impl::kbd::Keyboard kbd;
    impl::mouse::Mouse mouse;

    // Frame rate
    impl::framerate::FrameRateAdjuster fra(impl::config::GetFrameRate());
    impl::framerate::FrameRateMeasurer frm;
    double measured_frame_rate = 0.0;

    // Main loop
    bool quits = false;
    while (!quits) {
        // Handle events
        quits = impl::revent::HandleEvents(kbd, mouse);

        // DEBUG
        //std::cout << "x:" << mouse.x() << " y:" << mouse.y()
        //          << " dx:" << mouse.dx() << " dy:" << mouse.dy()
        //          << " scrolls:" << mouse.scrolls() << std::endl;
        if (mouse.Presses(impl::mouse::ButtonCode::kLeft)) {
            std::cout << "L" << std::endl;
        }
        if (mouse.Pressing(impl::mouse::ButtonCode::kRight)) {
            std::cout << "R" << std::endl;
        }
        if (mouse.Releases(impl::mouse::ButtonCode::kMiddle)) {
            std::cout << "M" << std::endl;
        }

        // Keyboard & mouse
        kbd.Update();
        mouse.Update();

        // Frame rate
        if (frm.MeasureFrameRate(measured_frame_rate)) {
            std::cout << measured_frame_rate << " fps" << std::endl;
        }
        fra.Adjust();
    }
}

}  // namespace windfall::routine::debug
