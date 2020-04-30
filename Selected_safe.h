#ifndef PS_JV_GRAPHICS_FINAL_SELECTED_SAFE_H
#define PS_JV_GRAPHICS_FINAL_SELECTED_SAFE_H

#include "Tile.h"

class Selected_safe : public Tile {
public:
    Selected_safe();
    void draw() const override;
};

#endif //PS_JV_GRAPHICS_FINAL_SELECTED_SAFE_H
