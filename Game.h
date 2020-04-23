#ifndef PS_JV_GRAPHICS_FINAL_GAME_H
#define PS_JV_GRAPHICS_FINAL_GAME_H

#include "Bomb.h"
#include "Safe_Space.h"
#include "Tile.h"
#include "Unselected_tile.h"
#include "Selected_safe_tile.h"
#include "Selected_bomb_tile.h"

#include <iostream>
#include <memory>
#include <ctime>
#include <vector>

using namespace std;

class Game {
private:
    vector<vector<unique_ptr<Tile>>> completed_board; // master board data/info
    // vector<vector<unique_ptr<Tile>>> board; // user sees this, starts empty
    int game_dimension;
    int tile_height = 8, tile_width = 8;
    int bomb_count;

public:
    Game() {
        game_dimension = 8;
        bomb_count = 10;
    }

    void run() {
        completed_board = create_board();
        add_bombs();
        print(completed_board);
    }

    void set_tile_height(int tile_height) {
        this->tile_height = tile_height;
    }

    void set_tile_width(int tile_width) {
        this->tile_width = tile_width;
    }

    void set_bomb_count(int bomb_count) {
        this->bomb_count = bomb_count;
    }

    int get_tile_width() const {
        return tile_width;
    }

    int get_tile_height() const {
        return tile_height;
    }

    vector<vector<unique_ptr<Tile>>> create_board() {
        vector<vector<unique_ptr<Tile>>> new_board;
        for (int y = 0; y < tile_height; ++y) {
            // TODO: Remove row2
            vector<unique_ptr<Tile>> row2;
            //vector<unique_ptr<Tile>> row;
            for (int x = 0; x < tile_width; ++x) {
                // TODO: Remove adding safe space
                Safe_Space safe_space;
                row2.push_back(move(make_unique<Safe_Space>(safe_space)));


                //Unselected_tile unselected_tile(x,y);
                //row.push_back(move(make_unique<Unselected_tile>(unselected_tile)));
            }
            // TODO: Change to row
            new_board.push_back(move(row2));
        }
        return new_board;
    }

    void add_bombs() {
        vector<int> bomb_coordinates;

        srand(time(nullptr));
        int x; // row
        int y; // column

        for (int i = 0; i < bomb_count; ++i) {
            x = rand() % tile_width;
            y = rand() % tile_height;

            Bomb bomb;
            unique_ptr<Bomb> unique_bomb_ptr = make_unique<Bomb>(bomb);
            completed_board[x][y] = move(unique_bomb_ptr);
            update_safe_spaces_helper(x, y);
        }
    }

    void update_safe_spaces_helper(int x, int y) {
        int index_out_of_bounds = game_dimension - 1;

        // edge cases for top three adjacent positions
        if (x > 0) {
            if (y > 0) { update_safe_spaces(x - 1, y - 1); } // top left
            if (y < index_out_of_bounds) { update_safe_spaces(x - 1, y + 1); } // top right
            update_safe_spaces(x - 1, y); // top
        }

        // edge cases for bottom three adjacent positions
        if (x < index_out_of_bounds) {
            if (y < index_out_of_bounds) { update_safe_spaces(x + 1, y + 1); } // bottom right
            if (y > 0) { update_safe_spaces(x + 1, y - 1); } // bottom left
            update_safe_spaces(x + 1, y); // bottom
        }

        // edge cases for left and right adjacent positions
        if (y < index_out_of_bounds) { update_safe_spaces(x, y + 1); }  // right
        if (y > 0) { update_safe_spaces(x, y - 1); }                    // left
    }

    void update_safe_spaces(int x, int y) {
        int adjacent_bombs = completed_board[x][y]->get_adj_bombs();
        if (adjacent_bombs != -1) {
            adjacent_bombs++;
        }
        completed_board[x][y]->set_adj_bombs(adjacent_bombs);
    }

    void print(vector<vector<unique_ptr<Tile>>> &board) {
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[i].size(); ++j) {
                cout << " | " << board[i][j]->tile_display();
            }
            cout << " |" << endl;
        }
        cout << endl;
    }

    /*void create_board(vector<vector<unique_ptr<Tile>>> &board, double height, double width, double padding) const{
        double x = padding, y = 0;
        double h = (height)/ tile_height;
        double w = (width - padding)/ tile_width;

        for (int row = 0; row < tile_height; row ++) {
            for (int col = 0; col < tile_width; col ++) {
                board[row][col]->draw(x, y, w, h, row, col);
                x += w;
            }
            x = padding;
            y += h;
        }
    }*/

};

#endif //PS_JV_GRAPHICS_FINAL_GAME_H
