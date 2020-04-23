#ifndef PS_JV_GRAPHICS_FINAL_UNCOVERED_SAFE_TILE_H
#define PS_JV_GRAPHICS_FINAL_UNCOVERED_SAFE_TILE_H


#import "Tile.h"



class Selected_safe_tile: public Tile {
protected:
    int adj_bombs;
public:
    Selected_safe_tile();
    Selected_safe_tile(int row, int column, int adj_bombs);

    int get_adj_bombs() const;
    void set_adj_bombs(int adj_bombs);

    //void draw(double x, double y, double width, double height, int tile_width, int tile_height, double padding) const override;
};

#endif //PS_JV_GRAPHICS_FINAL_UNCOVERED_SAFE_TILE_H
