#ifndef PS_JV_GRAPHICS_FINAL_SELECTED_BOMB_H
#define PS_JV_GRAPHICS_FINAL_SELECTED_BOMB_H

#include "Tile.h"

class Selected_bomb : public Tile {
public:
    /**
     * Constructor
     */
    Selected_bomb();

    /**
     * Draws the tile, and bomb graphic in the correct location
     */
    void draw() const override;
};

#endif //PS_JV_GRAPHICS_FINAL_SELECTED_BOMB_H
