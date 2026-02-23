#include "field/tile.h"

#include <array>

#include "system/assert.h"

namespace windfall::field::tile {

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
}

const Tile& GetTile(TileId tile_id)
{
    int index = static_cast<int>(tile_id);
    INUK_ASSERT((0 <= index) && (index < static_cast<int>(TileId::kMax)));
    return gTileDict[index];
}

}  // namespace windfall::field::tile
