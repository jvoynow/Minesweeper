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

/*    void draw(double x, double y, double width, double height, int row, int col) const override {
        if (row % 2 == 0) {
            ++col;
        }
        if (col % 2 == 1) {
            glColor3f(colors[LIGHT_BROWN].r, colors[LIGHT_BROWN].g,colors[LIGHT_BROWN].b);
        } else {
            glColor3f(colors[DARK_BROWN].r, colors[DARK_BROWN].g,colors[DARK_BROWN].b);
        }
        glBegin(GL_QUADS);
        glVertex2i( x + 0 * width, y + 0 * height);
        glVertex2i(x + 1 * width, y + 0 * height);
        glVertex2i(x + 1 * width, y + 1 * height);
        glVertex2i(x + 0 * width, y + 1 * height);
        glEnd();


        // TODO: Draw number here
    }*/

};


#endif //PS_JV_GRAPHICS_FINAL_SAFE_SPACE_H
