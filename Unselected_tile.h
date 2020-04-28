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
        glColor3f(0,1,0);
        glBegin(GL_QUADS);
        glVertex2i(x1, y1);
        glVertex2i(x2, y1);
        glVertex2i(x2, y2);
        glVertex2i(x1, y2);
        glEnd();
    }
};


#endif //PS_JV_GRAPHICS_FINAL_UNSELECTED_TILE_H
