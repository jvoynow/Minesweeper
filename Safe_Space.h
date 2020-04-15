//
// Created by voyno on 4/15/2020.
//

#ifndef PS_JV_GRAPHICS_FINAL_SAFE_SPACE_H
#define PS_JV_GRAPHICS_FINAL_SAFE_SPACE_H

#include "Tile.h"

#include <string>
#include <sstream>

class Safe_Space : public Tile {
public:
    Safe_Space() {
        adjacent_bombs = 0;
    }

    string tile_display() override {
        stringstream ss;
        ss << get_adjacent_bombs();
        string str = ss.str();
        return str;
    }

};


#endif //PS_JV_GRAPHICS_FINAL_SAFE_SPACE_H
