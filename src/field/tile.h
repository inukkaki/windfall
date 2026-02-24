#ifndef WINDFALL_FIELD_TILE_H_
#define WINDFALL_FIELD_TILE_H_

#include "graphics/texture.h"

namespace windfall::field::tile {

namespace impl {

namespace texture = windfall::graphics::texture;

}  // namespace impl

inline constexpr int kTileWidth = 16;
inline constexpr int kTileHeight = 16;

enum class TileId : unsigned char {
    kAir,
    kUnknown,
    kBlock,
    kMax,
};

enum class TileCollisionShape : unsigned char {
    kNone,
    kSquare,
};

struct TileCollision {
    TileCollisionShape shape;

    bool closed_t;  // At the top
    bool closed_l;  // On the left
    bool closed_r;  // On the right
    bool closed_b;  // At the bottom

    TileCollision() = default;
};

struct Tile {
    TileId id;
    TileCollision collision;

    Tile() = default;

    void RenderDebugInfo(
        const impl::texture::Texture& target, int row, int col) const;
};

void SetTileDict();

const Tile& GetTile(TileId tile_id);

}  // namespace windfall::field::tile

#endif  // WINDFALL_FIELD_TILE_H_
