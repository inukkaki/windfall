#include "entity/delegate.h"

#include <algorithm>
#include <cmath>

#include "entity/base.h"
#include "field/field.h"
#include "field/tile.h"
#include "math/vector.h"
#include "system/assert.h"

namespace windfall::entity::delegate {

namespace impl {

namespace ebase = windfall::entity::base;
namespace field = windfall::field::field;
namespace tile = windfall::field::tile;
namespace vector = windfall::math::vector;

}  // namespace impl

namespace {

void DetectCollisionDownward(
    const impl::ebase::Positional& pos, const impl::vector::Vector2D& delta_r)
{
    INUK_ASSERT(pos.v.y > 0.0f);

    // Calculate the range of rows to scan
    float anchor_y = pos.r.y + pos.collision.h;
    int s_row = static_cast<int>(std::floor(anchor_y/impl::tile::kTileHeight));
    int e_row = static_cast<int>(
        std::floor((anchor_y + delta_r.y)/impl::tile::kTileHeight));

    // Scan the rows of the field
    for (int i = s_row; i <= e_row; ++i) {
        // Calculate the range of columns to scan
        float d1 = std::clamp(
            impl::tile::kTileHeight*(i + 1) - anchor_y,
            0.0f, delta_r.y)/delta_r.y;
        float d2 = std::clamp(
            impl::tile::kTileHeight*i - anchor_y, 0.0f, delta_r.y)/delta_r.y;
        int s_col = -1;
        int e_col = -1;
        if (pos.v.x < 0.0f) {
            s_col = static_cast<int>(
                std::floor((pos.r.x + d1*delta_r.x)/impl::tile::kTileWidth));
            e_col = static_cast<int>(
                std::floor((pos.r.x + pos.collision.w - 1.0f + d2*delta_r.x)
                    /impl::tile::kTileWidth));
        } else {
            s_col = static_cast<int>(
                std::floor((pos.r.x + d2*delta_r.x)/impl::tile::kTileWidth));
            e_col = static_cast<int>(
                std::floor((pos.r.x + pos.collision.w - 1.0f + d1*delta_r.x)
                    /impl::tile::kTileWidth));
        }

        // Scan the columns of the field
        for (int j = s_col; j <= e_col; ++j) {
            // DEBUG
            impl::field::IncrementReferenceCount(i, j);
        }
    }
}

void DetectCollision(impl::ebase::BaseEntity& self, float dt)
{
    // TODO: Implement this function.
    const impl::ebase::Positional& pos = self.pos();
    impl::vector::Vector2D delta_r = pos.v*dt;
    if (pos.v.y < 0.0f) {
        // Upward
    } else if (pos.v.y > 0.0f) {
        DetectCollisionDownward(pos, delta_r);
    }
    if (pos.v.x < 0.0f) {
        // Leftward
    } else if (pos.v.x > 0.0f) {
        // Rightward
    }
}

}  // namespace

void GeneralMotion::Move(impl::ebase::BaseEntity& self, float dt)
{
    self.UpdateA();
    self.UpdateV(dt);
    DetectCollision(self, dt);
    self.UpdateR(dt);
}

}  // namespace windfall::entity::delegate
