#ifndef WINDFALL_FIELD_FIELD_H_
#define WINDFALL_FIELD_FIELD_H_

#include <vector>

#include "field/tile.h"
#include "system/assert.h"

namespace windfall::field::field {

namespace impl {

namespace tile = windfall::field::tile;

}  // namespace impl

using TileIdArray = std::vector<std::vector<impl::tile::TileId>>;

class Field {
public:
    Field(int width, int height) : w_(width), h_(height)
    {
        InitArray(width, height);
    }

    int w() const { return w_; }
    int h() const { return h_; }

    void InitArray(int width, int height);
    void Load();  // TODO: Load the field data from external files.

    const impl::tile::Tile& GetCollisionTile(int row, int col) const;

private:
    int w_;  // Width
    int h_;  // Height

    TileIdArray collision_tiles_;
};

}  // namespace windfall::field::field

#endif  // WINDFALL_FIELD_FIELD_H_
