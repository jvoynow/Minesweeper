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
    vector<vector<unique_ptr<Tile>>> user_interface_board; // user sees this, starts empty
    int num_rows, num_cols;
    int bomb_count;

public:
    Game(int num_rows, int num_cols, int bomb_count) {
        this->num_rows = num_rows;
        this->num_cols = num_cols;
        this->bomb_count = bomb_count;
    }

    void initialize() {
        completed_board = create_board(false);
        user_interface_board = create_board(true);

        add_bombs();
        print(completed_board);

        print(user_interface_board);
    }

    void set_num_rows(int num_rows) {
        this->num_rows = num_rows;
    }

    void set_num_cols(int num_cols) {
        this->num_cols = num_cols;
    }

    void set_bomb_count(int bomb_count) {
        this->bomb_count = bomb_count;
    }

    int get_num_rows() const {
        return num_rows;
    }

    int get_num_cols() const {
        return num_cols;
    }

    vector<vector<unique_ptr<Tile>>> create_board(bool blank) {
        vector<vector<unique_ptr<Tile>>> new_board;
        for (int y = 0; y < num_rows; ++y) {
            vector<unique_ptr<Tile>> row;
            for (int x = 0; x < num_cols; ++x) {
                if (blank) {
                    Unselected_tile unselected;
                    row.push_back(move(make_unique<Unselected_tile>(unselected)));
                } else {
                    Safe_Space space;
                    row.push_back(move(make_unique<Safe_Space>(space)));
                }
            }
            new_board.push_back(move(row));
        }
        return new_board;
    }

    void add_bombs() {
        vector<int> bomb_coordinates;

        srand(time(nullptr));
        int x; // row
        int y; // column

        for (int i = 0; i < bomb_count; ++i) {
            x = rand() % num_rows;
            y = rand() % num_cols;

            // check if bomb exists in given position
            if (completed_board[x][y]->get_adj_bombs() != -1) {
                Bomb bomb;
                unique_ptr<Bomb> unique_bomb_ptr = make_unique<Bomb>(bomb);
                completed_board[x][y] = move(unique_bomb_ptr);
                update_safe_spaces_helper(x, y);
            }
        }
    }

    void update_safe_spaces_helper(int x, int y) {
        int row_out_of_bounds = num_rows - 1;
        int col_out_of_bounds = num_cols - 1;

        // edge cases for top three adjacent positions
        if (x > 0) {
            if (y > 0) { update_safe_spaces(x - 1, y - 1); } // top left
            if (y < col_out_of_bounds) { update_safe_spaces(x - 1, y + 1); } // top right
            update_safe_spaces(x - 1, y); // top
        }

        // edge cases for bottom three adjacent positions
        if (x < row_out_of_bounds) {
            if (y < col_out_of_bounds) { update_safe_spaces(x + 1, y + 1); } // bottom right
            if (y > 0) { update_safe_spaces(x + 1, y - 1); } // bottom left
            update_safe_spaces(x + 1, y); // bottom
        }

        // edge cases for left and right adjacent positions
        if (y < col_out_of_bounds) { update_safe_spaces(x, y + 1); }  // right
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
