//
// Created by voyno on 4/23/2020.
//

#ifndef PS_JV_GRAPHICS_FINAL_FLAG_H
#define PS_JV_GRAPHICS_FINAL_FLAG_H

#include "Tile.h"

#include <string>

class Flag : public Tile {
public:
    Flag() {
    }

    string tile_display() override {
        return ">";
    }
};

#endif //PS_JV_GRAPHICS_FINAL_FLAG_H
