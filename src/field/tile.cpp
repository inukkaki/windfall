#include "field/tile.h"

#include <array>

#include "graphics/texture.h"
#include "system/assert.h"

namespace windfall::field::tile {

namespace impl {

namespace texture = windfall::graphics::texture;

}  // namespace impl

namespace {

void RenderSquareCollision(
    const impl::texture::Texture& target, const Tile& tile, int row, int col)
{
    int x1 = kTileWidth*col;
    int y1 = kTileHeight*row;
    int x2 = kTileWidth*(col + 1) - 1;
    int y2 = kTileHeight*(row + 1) - 1;
    if (tile.collision.closed_t) { target.DrawLine(x1, y1, x2, y1); }
    if (tile.collision.closed_l) { target.DrawLine(x1, y1, x1, y2); }
    if (tile.collision.closed_r) { target.DrawLine(x2, y1, x2, y2); }
    if (tile.collision.closed_b) { target.DrawLine(x1, y2, x2, y2); }
}

}  // namespace

void Tile::RenderDebugInfo(
    const impl::texture::Texture& target, int row, int col) const
{
    if (id == TileId::kUnknown) {
        target.SetDrawColor(0xff, 0x00, 0x00, 0xff);
        target.DrawRect(
            kTileWidth*col, kTileHeight*row, kTileWidth, kTileHeight);
    } else {
        target.SetDrawColor(0xff, 0xff, 0xff, 0xff);
        switch (collision.shape) {
        case TileCollisionShape::kSquare:
            RenderSquareCollision(target, *this, row, col);
            break;
        default:
            break;
        }
    }
}

namespace {

std::array<Tile, static_cast<int>(TileId::kMax)> gTileDict;

}  // namespace

void SetTileDict()
{
    // DEBUG
    int index;
    for (index = 0; index < static_cast<int>(TileId::kMax); ++index) {
        gTileDict[index].id = static_cast<TileId>(index);
    }

    index = static_cast<int>(TileId::kAir);
    gTileDict[index].collision.shape = TileCollisionShape::kNone;

    index = static_cast<int>(TileId::kUnknown);
    gTileDict[index].collision.shape = TileCollisionShape::kNone;

    index = static_cast<int>(TileId::kBlock);
    gTileDict[index].collision.shape = TileCollisionShape::kSquare;
    gTileDict[index].collision.closed_t = true;
    gTileDict[index].collision.closed_l = true;
    gTileDict[index].collision.closed_r = true;
    gTileDict[index].collision.closed_b = true;
}

const Tile& GetTile(TileId tile_id)
{
    int index = static_cast<int>(tile_id);
    INUK_ASSERT((0 <= index) && (index < static_cast<int>(TileId::kMax)));
    return gTileDict[index];
}

}  // namespace windfall::field::tile
