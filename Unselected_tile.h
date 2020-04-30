#ifndef PS_JV_GRAPHICS_FINAL_UNSELECTED_TILE_H
#define PS_JV_GRAPHICS_FINAL_UNSELECTED_TILE_H

#include "Tile.h"

class Unselected_tile: public Tile {
public:
    Unselected_tile();
    Unselected_tile(int row, int column);

    void draw() const override;
};


#endif //PS_JV_GRAPHICS_FINAL_UNSELECTED_TILE_H
