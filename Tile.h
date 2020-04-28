#ifndef PS_JV_GRAPHICS_FINAL_TILE_H
#define PS_JV_GRAPHICS_FINAL_TILE_H


#include <iostream>
#include <string>
#include "Graphics.h"


using namespace std;

struct color {
    double r, g, b;
};

class Tile {
protected:
    bool display;
    bool local_search_flag;

    int adj_bombs;
    int row, column;
    color current_fill, original_fill, hover_fill;
    double x1, x2, y1, y2;
public:
    Tile() {
        display = false;
        local_search_flag = false;
    }

    bool get_display() {
        return display;
    }

    bool get_local_search_flag() const {
        return local_search_flag;
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

    void set_local_search_flag(bool flag) {
        local_search_flag = flag;
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

    void set_x1(double x1) {
        this->x1 = x1;
    }

    void set_x2(double x2) {
        this->x2 = x2;
    }

    void set_y1(double y1) {
        this->y1 = y1;
    }

    void set_y2(double y2) {
        this->y2 = y2;
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

    bool is_overlapping(int x, int y) const {
        return x >= x1 && y >= y1 && x <= x2 && y <= y2;
    }

    virtual void draw() const = 0;

};

#endif //PS_JV_GRAPHICS_FINAL_TILE_H
