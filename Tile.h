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
    int row, column;
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

    void set_row(int row) {
        this->row = row;
    }

    void set_column(int column) {
        this->column = column;
    }

    int get_row() const {
        return row;
    }

    int get_column() const {
        return column;
    }

    void add_adjacent_bomb() {
        set_adjacent_bombs(get_adjacent_bombs() + 1);
    }

    virtual string tile_display() {
        return "-";
    }

    virtual void draw(double x, double y, double width, double height) const {
    }

};

#endif //PS_JV_GRAPHICS_FINAL_TILE_H
