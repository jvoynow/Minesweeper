//
// Created by voyno on 4/15/2020.
//

#ifndef PS_JV_GRAPHICS_FINAL_BOMB_H
#define PS_JV_GRAPHICS_FINAL_BOMB_H

#include "Tile.h"

#include <string>

class Bomb : public Tile {
public:
    Bomb() {
        adjacent_bombs = -1;
    }

    string tile_display() override {
        return "B";
    }
};

#endif //PS_JV_GRAPHICS_FINAL_BOMB_H
