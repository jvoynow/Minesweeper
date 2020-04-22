#ifndef PS_JV_GRAPHICS_FINAL_TILE_H
#define PS_JV_GRAPHICS_FINAL_TILE_H

#include <iostream>
#include <string>
#include "graphics.h"

using namespace std;

class Tile {
protected:
    bool display;
    int adj_bombs;
    int row, column;
    color current_fill, original_fill, hover_fill;
    double x1, x2, y1, y2;
public:
    Tile() {
        display = false;
    }

    bool get_display() {
        return display;
    }

    int get_row() const {
        return row;
    }

    int get_column() const {
        return column;
    }

    int get_adj_bombs() {
        return adj_bombs;
    }

    void set_current_fill(color fill) {
        current_fill = fill;
    }

    void set_original_fill(color fill) {
        original_fill = fill;
    }

    void set_hover_fill(color fill) {
        hover_fill = fill;
    }

    void set_display(bool display) {
        this->display = display;
    }

    void set_adj_bombs(int a_b) {
        adj_bombs = a_b;
    }

    void set_row(int row) {
        this->row = row;
    }

    void set_column(int column) {
        this->column = column;
    }

    void hover() {
        set_current_fill(hover_fill);
    }

    void stop_hover() {
        set_current_fill(original_fill);
    }

    void add_adj_bomb() {
        set_adj_bombs(get_adj_bombs() + 1);
    }

    virtual string tile_display() {
        return "-";
    }

    bool is_overlapping(int x, int y) const {
        return x >= x1 && y >= y1 && x <= x2 && y <= y2;
    }

    virtual void draw(double x, double y, double width, double height, int tile_width, int tile_height, double padding) const {
        glColor3f(current_fill.r, current_fill.g,current_fill.b);
        glBegin(GL_QUADS);
        glVertex2i(x + 0 * ((width - padding)/ tile_width), y + 0 * (height / tile_height));
        glVertex2i(x + 1 * ((width - padding)/ tile_width), y + 0 * (height / tile_height));
        glVertex2i(x + 1 * ((width - padding)/ tile_width), y + 1 * (height / tile_height));
        glVertex2i(x + 0 * ((width - padding)/ tile_width), y + 1 * (height / tile_height));
        glEnd();
    }

};

#endif //PS_JV_GRAPHICS_FINAL_TILE_H
