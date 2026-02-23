#include "routine/debug.h"

#include <iostream>
#include <memory>

#include "SDL2/SDL.h"

#include "entity/base.h"
#include "entity/delegate.h"
#include "entity/entity.h"
#include "graphics/texture.h"
#include "interface/keyboard.h"
#include "interface/mouse.h"
#include "math/vector.h"
#include "routine/event.h"
#include "system/config.h"
#include "time/framerate.h"

namespace windfall::routine::debug {

namespace impl {

namespace ebase = windfall::entity::base;
namespace edlgt = windfall::entity::delegate;
namespace entity = windfall::entity::entity;
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
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
    SDL_RenderClear(renderer);

    impl::texture::Texture texture(renderer);
    texture.CreateTexture(
        impl::config::kWindowBaseWidth, impl::config::kWindowBaseHeight);
    impl::texture::RenderRect src_rect(
        0, 0, impl::config::kWindowBaseWidth, impl::config::kWindowBaseHeight);

    // Entity
    impl::entity::Entity player(
        impl::ebase::PhysicalProperty(2.0, 4.0f),
        std::make_unique<impl::edlgt::GeneralMotion>());
    float dt = impl::config::GetFrameDuration();

    impl::vector::Vector2D g(0.0f, 200.0f);

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
        texture.Clear(0x1f, 0x3f, 0x6f, 0xff);

        impl::vector::Vector2D force;
        if (kbd.Pressing(impl::kbd::KeyCode::kLeft)) {
            force += impl::vector::Vector2D(-1.0f, 0.0f);
        }
        if (kbd.Pressing(impl::kbd::KeyCode::kRight)) {
            force += impl::vector::Vector2D(1.0f, 0.0f);
        }
        if (kbd.Pressing(impl::kbd::KeyCode::kUp)) {
            force += impl::vector::Vector2D(0.0f, -1.0f);
        }
        if (kbd.Pressing(impl::kbd::KeyCode::kDown)) {
            force += impl::vector::Vector2D(0.0f, 1.0f);
        }
        force *= 500.0f;
        player.AddForce(force);
        player.AddForce(player.CalcDrag(1.0f));
        player.AddForce(player.CalcGravity(g));

        player.Move(dt);

        player.RenderDebugInfo(texture);

        texture.Render(nullptr, src_rect, 0.0f, 0.0f);
        SDL_RenderPresent(renderer);

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
