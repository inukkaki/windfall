#include "routine/debug.h"

#include <iostream>
#include <memory>

#include "SDL2/SDL.h"

#include "entity/base.h"
#include "entity/delegate.h"
#include "entity/entity.h"
#include "field/field.h"
#include "field/tile.h"
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
namespace field = windfall::field::field;
namespace tile = windfall::field::tile;
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

    // Field
    impl::field::Field field(25, 16);
    field.Load();

    impl::texture::Texture field_texture(renderer);
    field_texture.CreateTexture(
        impl::config::kWindowBaseWidth, impl::config::kWindowBaseHeight);
    field_texture.Clear(0x20, 0x40, 0x70, 0xff);
    for (int i = 0; i < field.h(); ++i) {
        for (int j = 0; j < field.w(); ++j) {
            field.GetCollisionTile(i, j).RenderDebugInfo(field_texture, i, j);
        }
    }

    impl::field::InitReferenceCountArray(field.w(), field.h());

    impl::texture::Texture ref_texture(renderer);
    ref_texture.CreateTexture(
        impl::config::kWindowBaseWidth, impl::config::kWindowBaseHeight);

    // Entity
    impl::ebase::Positional pos;
    pos.collision.w = 39;
    pos.collision.h = 20;
    impl::ebase::PhysicalProperty phys;
    phys.mass = 2.0f;
    phys.drag_factor = 4.0f;
    impl::entity::Entity player(
        pos, phys, std::make_unique<impl::edlgt::GeneralMotion>());

    player.ModifyR(
        impl::vector::Vector2D(50.0f, 20.0f),
        impl::ebase::VectorModificationMode::kAssign);

    impl::vector::Vector2D g(0.0f, 500.0f);

    impl::vector::Vector2D r(100.0f, 50.0f);

    // Keyboard & mouse
    impl::kbd::Keyboard kbd;
    impl::mouse::Mouse mouse;

    // Frame rate
    //impl::config::SetFrameRate(30);
    float dt = impl::config::GetFrameDuration();

    impl::framerate::FrameRateAdjuster fra(impl::config::GetFrameRate());
    impl::framerate::FrameRateMeasurer frm;
    double measured_frame_rate = 0.0;

    // Main loop
    bool quits = false;
    while (!quits) {
        // Handle events
        quits = impl::revent::HandleEvents(kbd, mouse);

        // DEBUG
        texture.Clear(0x1f, 0x3f, 0x6f, 0x00);

            // Reference count (field)
            ref_texture.Clear(0x00, 0x00, 0x00, 0x00);
            for (int i = 0; i < field.h(); ++i) {
                for (int j = 0; j < field.w(); ++j) {
                    if (impl::field::GetReferenceCount(i, j) > 0) {
                        ref_texture.SetDrawColor(0xff, 0x00, 0xff, 0x3f);
                        ref_texture.FillRect(
                            impl::tile::kTileWidth*j,
                            impl::tile::kTileHeight*i,
                            impl::tile::kTileWidth, impl::tile::kTileHeight);
                        ref_texture.SetDrawColor(0xff, 0x00, 0xff, 0x7f);
                        ref_texture.DrawRect(
                            impl::tile::kTileWidth*j,
                            impl::tile::kTileHeight*i,
                            impl::tile::kTileWidth, impl::tile::kTileHeight);
                        impl::field::ResetReferenceCount(i, j);
                    }
                }
            }

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
        force *= 2500.0f;
        player.AddForce(force);
        //player.AddForce(player.CalcDrag(1.0f));
        //player.AddForce(player.CalcGravity(g));

        player.Move(dt);
        impl::vector::Vector2D delta_r;
        if (kbd.Pressing(impl::kbd::KeyCode::kW)) { delta_r.y -= 1.0f; }
        if (kbd.Pressing(impl::kbd::KeyCode::kA)) { delta_r.x -= 1.0f; }
        if (kbd.Pressing(impl::kbd::KeyCode::kS)) { delta_r.y += 1.0f; }
        if (kbd.Pressing(impl::kbd::KeyCode::kD)) { delta_r.x += 1.0f; }
        r += delta_r;
        player.ModifyR(r, impl::ebase::VectorModificationMode::kAssign);

            // Loop at the edge of the screen
            impl::vector::Vector2D r = player.pos().r;
            bool loop_flag = false;
            if (r.x < 0) { r.x += 480; loop_flag = true; }
            if (r.y < 0) { r.y += 360; loop_flag = true; }
            if (r.x > 479) { r.x -= 480; loop_flag = true; }
            if (r.y > 359) { r.y -= 360; loop_flag = true; }
            if (loop_flag) {
                player.ModifyR(
                    r, impl::ebase::VectorModificationMode::kAssign);
            }

        player.RenderDebugInfo(texture);

        field_texture.Render(nullptr, src_rect, 0.0f, 0.0f);
        ref_texture.Render(nullptr, src_rect, 0.0f, 0.0f);
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
