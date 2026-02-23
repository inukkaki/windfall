#include "entity/base.h"

#include <string>

#include "graphics/texture.h"
#include "math/vector.h"
#include "system/modal.h"

namespace windfall::entity::base {

namespace impl {

namespace texture = windfall::graphics::texture;
namespace vector = windfall::math::vector;
namespace modal = windfall::system::modal;

}  // namespace impl

impl::vector::Vector2D BaseEntity::CalcGravity(
    const impl::vector::Vector2D& g) const
{
    return phys_.mass*g;
}

impl::vector::Vector2D BaseEntity::CalcDrag(float fluid_factor) const
{
    float drag_coeff = phys_.drag_factor*fluid_factor;
    return -drag_coeff*pos_.v;
}

namespace {

void ModifyVector(
    impl::vector::Vector2D& lhs, const impl::vector::Vector2D& rhs,
    VectorModificationMode mode)
{
    switch (mode) {
    case VectorModificationMode::kAdd:
        lhs += rhs;
        break;
    case VectorModificationMode::kSubtract:
        lhs -= rhs;
        break;
    case VectorModificationMode::kAssign:
        lhs = rhs;
        break;
    default:
        impl::modal::ShowErrorMessage(
            "BaseEntity Error",
            "Invalid VectorModificationMode value.",
            std::to_string(static_cast<int>(mode)).c_str());
        break;
    }
}

}  // namespace

void BaseEntity::ModifyA(
    const impl::vector::Vector2D& vec, VectorModificationMode mode)
{
    ModifyVector(pos_.a, vec, mode);
}

void BaseEntity::ModifyV(
    const impl::vector::Vector2D& vec, VectorModificationMode mode)
{
    ModifyVector(pos_.v, vec, mode);
}

void BaseEntity::ModifyR(
    const impl::vector::Vector2D& vec, VectorModificationMode mode)
{
    ModifyVector(pos_.r, vec, mode);
}

void BaseEntity::AddForce(const impl::vector::Vector2D& force)
{
    pos_.f += force;
}

void BaseEntity::UpdateA()
{
    pos_.a = pos_.f/phys_.mass;
    pos_.f.Zero();
}

void BaseEntity::UpdateV(float dt)
{
    pos_.v += pos_.a*dt;
}

void BaseEntity::UpdateR(float dt)
{
    pos_.r += pos_.v*dt;
}

namespace {

constexpr int kRenderEntityRSize = 8;
constexpr float kRenderEntityVSize = 8.0f/60;
constexpr float kRenderEntityASize = 8.0f/60;

void RenderEntityR(const impl::texture::Texture& target, const Positional& pos)
{
    target.SetDrawColor(0xff, 0xff, 0xff, 0xff);
    target.DrawLine(
        pos.r.x - kRenderEntityRSize, pos.r.y,
        pos.r.x + kRenderEntityRSize, pos.r.y);
    target.DrawLine(
        pos.r.x, pos.r.y - kRenderEntityRSize,
        pos.r.x, pos.r.y + kRenderEntityRSize);
}

void RenderEntityV(const impl::texture::Texture& target, const Positional& pos)
{
    target.SetDrawColor(0xff, 0xff, 0x00, 0xff);
    target.DrawVector(kRenderEntityVSize*pos.v, pos.r);
}

void RenderEntityA(const impl::texture::Texture& target, const Positional& pos)
{
    target.SetDrawColor(0xff, 0x00, 0x00, 0xff);
    target.DrawVector(kRenderEntityASize*pos.a, pos.r);
}

}  // namespace

void BaseEntity::RenderDebugInfo(const impl::texture::Texture& target) const
{
    RenderEntityR(target, pos_);
    RenderEntityV(target, pos_);
    RenderEntityA(target, pos_);
}

}  // namespace windfall::entity::base
