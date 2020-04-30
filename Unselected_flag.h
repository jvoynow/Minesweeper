#ifndef PS_JV_GRAPHICS_FINAL_UNSELECTED_FLAG_H
#define PS_JV_GRAPHICS_FINAL_UNSELECTED_FLAG_H

#include "Tile.h"

class Unselected_flag : public Tile {
public:
    Unselected_flag();
    void draw() const override;
};

#endif //PS_JV_GRAPHICS_FINAL_UNSELECTED_FLAG_H
