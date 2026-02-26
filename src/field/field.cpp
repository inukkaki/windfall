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
    collision_tiles_.assign(
        h_, std::vector<impl::tile::TileId>(w_, impl::tile::TileId::kAir));
}

void Field::Load()
{
    // DEBUG
    InitArray(25, 16);
    collision_tiles_[0][0] = impl::tile::TileId::kUnknown;
    collision_tiles_[0][24] = impl::tile::TileId::kUnknown;
    collision_tiles_[15][24] = impl::tile::TileId::kUnknown;
    for (int i = 10; i < 14; ++i) {
        for (int j = 5; j < 20; ++j) {
            collision_tiles_[i][j] = impl::tile::TileId::kBlock;
        }
    }
}

bool Field::Within(int row, int col) const
{
    bool cond_row = (0 <= row) && (row < h_);
    bool cond_col = (0 <= col) && (col < w_);
    return cond_row && cond_col;
}

const impl::tile::Tile& Field::GetCollisionTile(int row, int col) const
{
    impl::tile::TileId tile_id = impl::tile::TileId::kUnknown;
    if (Within(row, col)) {
        tile_id = collision_tiles_[row][col];
    }
    return impl::tile::GetTile(tile_id);
}

namespace {

std::vector<std::vector<int>> gReferenceCounts;
int gReferenceCountWidth = 0;
int gReferenceCountHeight = 0;

bool ReferenceCountWithin(int row, int col)
{
    bool cond_row = (0 <= row) && (row < gReferenceCountHeight);
    bool cond_col = (0 <= col) && (col < gReferenceCountWidth);
    return cond_row && cond_col;
}

}  // namespace

void InitReferenceCountArray(int width, int height)
{
    INUK_ASSERT(0 < width);
    INUK_ASSERT(0 < height);
    gReferenceCountWidth = width;
    gReferenceCountHeight = height;
    gReferenceCounts.assign(
        gReferenceCountHeight, std::vector<int>(gReferenceCountWidth, 0));
}

int GetReferenceCount(int row, int col)
{
    int ref = 0;
    if (ReferenceCountWithin(row, col)) {
        ref = gReferenceCounts[row][col];
    }
    return ref;
}

void IncrementReferenceCount(int row, int col)
{
    if (ReferenceCountWithin(row, col)) {
        ++gReferenceCounts[row][col];
    }
}

void ResetReferenceCount(int row, int col)
{
    if (ReferenceCountWithin(row, col)) {
        gReferenceCounts[row][col] = 0;
    }
}

}  // namespace windfall::field::field
