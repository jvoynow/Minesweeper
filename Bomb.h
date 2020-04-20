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

/*    void draw(double x, double y, double width, double height, int row, int col) const override{
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


        // TODO: Draw Bomb here
    }*/
};

#endif //PS_JV_GRAPHICS_FINAL_BOMB_H
