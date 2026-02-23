#ifndef WINDFALL_FIELD_TILE_H_
#define WINDFALL_FIELD_TILE_H_

namespace windfall::field::tile {

enum class TileId : unsigned char {
    kAir,
    kUnknown,
    kBlock,
    kMax,
};

struct Tile {
    TileId id;
};

void SetTileDict();

const Tile& GetTile(TileId tile_id);

}  // namespace windfall::field::tile

#endif  // WINDFALL_FIELD_TILE_H_
