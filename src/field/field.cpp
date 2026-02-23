#include "field/field.h"

#include <vector>

#include "field/tile.h"
#include "system/assert.h"

namespace windfall::field::field {

namespace impl {

namespace tile = windfall::field::tile;

}  // namespace impl

void Field::InitArray(int width, int height)
{
    INUK_ASSERT(0 < width);
    INUK_ASSERT(0 < height);
    w_ = width;
    h_ = height;
    collision_tiles_.clear();
    for (int i = 0; i < h_; ++i) {
        std::vector<
            impl::tile::TileId> tmp_tiles(w_, impl::tile::TileId::kAir);
        collision_tiles_.push_back(tmp_tiles);
    }
}

const impl::tile::Tile& Field::GetCollisionTile(int row, int col) const
{
    impl::tile::TileId tile_id = impl::tile::TileId::kUnknown;
    bool cond_row = (0 <= row) && (row < h_);
    bool cond_col = (0 <= col) && (col < w_);
    if (cond_row && cond_col) {
        tile_id = collision_tiles_[row][col];
    }
    return impl::tile::GetTile(tile_id);
}

}  // namespace windfall::field::field
