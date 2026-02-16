#include "routine/debug.h"

#include <iostream>

#include "SDL2/SDL.h"

#include "graphics/texture.h"
#include "interface/keyboard.h"
#include "interface/mouse.h"
#include "math/vector.h"
#include "routine/event.h"
#include "system/config.h"
#include "time/framerate.h"

namespace windfall::routine::debug {

namespace impl {

namespace texture = windfall::graphics::texture;
namespace kbd = windfall::interface::keyboard;
namespace mouse = windfall::interface::mouse;
namespace vector = windfall::math::vector;
namespace revent = windfall::routine::event;
namespace config = windfall::system::config;
namespace framerate = windfall::time::framerate;

}  // namespace impl

void DebugRoutine(SDL_Window* window, SDL_Renderer* renderer)
{
    // Graphics
    SDL_SetRenderTarget(renderer, nullptr);
    SDL_SetRenderDrawColor(renderer, 0x1f, 0x3f, 0x6f, 0xff);
    SDL_RenderClear(renderer);

    impl::texture::Texture texture(renderer);
    texture.CreateTexture(320, 240);
    texture.Clear(0x00, 0x00, 0x00, 0x7f);

    texture.SetDrawColor(0xff, 0xff, 0xff, 0xff);
    texture.DrawRect(0, 0, 320, 240);
    texture.DrawLine(0, 0, 4, 4);
    texture.DrawLine(10, 5, 200, 220);
    texture.DrawPoint(317, 3);
    texture.SetDrawColor(0xff, 0xff, 0x00, 0x4f);
    texture.FillRect(20, 120, 120, 80);

    impl::vector::Vector2D vec(5, 10);
    impl::vector::Vector2D offset_vec(30, 50);
    texture.SetDrawColor(0xff, 0x00, 0x00, 0xff);
    texture.DrawVector(vec, offset_vec);

    impl::texture::RenderRect src1(0, 0, 320, 240);
    texture.Render(nullptr, src1, 1.5f, 1.4f);
    impl::texture::RenderRect src2(0, 0, 60, 80, 10, 5);
    impl::texture::RenderRect dst1(322, 1, 60, 80);
    texture.Render(nullptr, src2, dst1);
    impl::texture::RenderRect dst2(350, 100, 60, 80);
    texture.Render(nullptr, src1, dst2);

    SDL_RenderPresent(renderer);

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
