//
// Created by voyno on 4/15/2020.
//

#ifndef PS_JV_GRAPHICS_FINAL_TILE_H
#define PS_JV_GRAPHICS_FINAL_TILE_H

#include <iostream>
#include <string>

using namespace std;

class Tile {
protected:
    bool display;
    int adjacent_bombs;
public:
    Tile() {
        display = false;
    }

    bool get_display() {
        return display;
    }
    int get_adjacent_bombs() {
        return adjacent_bombs;
    }

    void set_display(bool display) {
        this->display = display;
    }

    void set_adjacent_bombs(int a_b) {
        adjacent_bombs = a_b;
    }

    void add_adjacent_bomb() {
        set_adjacent_bombs(get_adjacent_bombs() + 1);
    }

    virtual string tile_display() {
        return "-";
    }

/*    virtual void draw(double x, double y, double width, double height, int row, int col) const {
        if (row % 2 == 0) {
            ++col;
        }
        if (col % 2 == 1) {
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

};

#endif //PS_JV_GRAPHICS_FINAL_TILE_H
