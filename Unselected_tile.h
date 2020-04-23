#ifndef PS_JV_GRAPHICS_FINAL_UNSELECTED_TILE_H
#define PS_JV_GRAPHICS_FINAL_UNSELECTED_TILE_H

#include "Tile.h"

class Unselected_tile: public Tile {
protected:
public:
    Unselected_tile(){
        row = 0;
        column = 0;
    }

    Unselected_tile(int row, int column) {
        this->row = row;
        this->column = column;
    }


/*void Unselected_tile::draw(double x, double y, double width, double height, int tile_width, int tile_height, double padding) const {
    int temp = column;
    if (row % 2 == 0) {
        ++temp;
    }
    if (temp % 2 == 1) {
        glColor3f(colors[LIGHT_GREEN].r, colors[LIGHT_GREEN].g,colors[LIGHT_GREEN].b);
    } else {
        glColor3f(colors[DARK_GREEN].r, colors[DARK_GREEN].g,colors[DARK_GREEN].b);
    }
    glBegin(GL_QUADS);
    glVertex2i( x + 0 * width, y + 0 * height);
    glVertex2i(x + 1 * width, y + 0 * height);
    glVertex2i(x + 1 * width, y + 1 * height);
    glVertex2i(x + 0 * width, y + 1 * height);
    glEnd();
}*/


    //void draw(double x, double y, double width, double height, int tile_width, int tile_height, double padding) const override;
};


#endif //PS_JV_GRAPHICS_FINAL_UNSELECTED_TILE_H
