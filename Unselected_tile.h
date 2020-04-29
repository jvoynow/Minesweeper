#ifndef PS_JV_GRAPHICS_FINAL_UNSELECTED_TILE_H
#define PS_JV_GRAPHICS_FINAL_UNSELECTED_TILE_H

#include "Tile.h"
#include "Graphics.h"

class Unselected_tile: public Tile {
public:
    Unselected_tile(){
        row = 0;
        column = 0;
    }

    Unselected_tile(int row, int column) {
        this->row = row;
        this->column = column;
    }


    void draw() const override {
        // TODO: Change this
        glColor3f(current_fill.r,current_fill.g,current_fill.b);
        glBegin(GL_QUADS);
        glVertex2i(c1, r1);
        glVertex2i(c2, r1);
        glVertex2i(c2, r2);
        glVertex2i(c1, r2);
        glEnd();
    }
};


#endif //PS_JV_GRAPHICS_FINAL_UNSELECTED_TILE_H
