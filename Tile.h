#ifndef PS_JV_GRAPHICS_FINAL_TILE_H
#define PS_JV_GRAPHICS_FINAL_TILE_H

#include <iostream>
#include <string>

struct color {
    double r, g, b;
};

class Tile {
protected:
    bool display, selected, flagged;

    int adj_bombs;
    int row, column;
    color current_fill, original_fill, hover_fill;
    double c1, c2, r1, r2;
public:
    Tile();
    bool get_flagged() const;

    int get_row() const;

    int get_column() const;

    int get_adj_bombs();

    void set_current_fill(color fill);

    void set_original_fill(color fill);

    void set_hover_fill(color fill);

    void set_adj_bombs(int a_b);

    void set_row(int row);

    void set_column(int column);

    void set_c1(double c1);

    void set_c2(double c2);

    void set_r1(double r1);

    void set_r2(double r2);

    void hover();

    void stop_hover();

    bool is_overlapping(int x, int y) const;

    virtual void draw() const = 0;

};

#endif //PS_JV_GRAPHICS_FINAL_TILE_H
