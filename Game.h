//
// Created by voyno on 4/15/2020.
//

#ifndef PS_JV_GRAPHICS_FINAL_GAME_H
#define PS_JV_GRAPHICS_FINAL_GAME_H

#include "Bomb.h"
#include "Safe_Space.h"
#include "Tile.h"

#include <iostream>
#include <memory>
#include <ctime>
#include <vector>

using namespace std;

class Game {
private:
    vector<vector<unique_ptr<Tile>>> completed_board; // master board data/info
    // vector<vector<Tile>> board; // user sees this, starts empty
    int game_dimension;
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

    vector<vector<unique_ptr<Tile>>> create_board() {
        vector<vector<unique_ptr<Tile>>> new_board;
        for (int i = 0; i < game_dimension; ++i) {

            vector<unique_ptr<Tile>> row;
            for (int j = 0; j < game_dimension; ++j) {
                Safe_Space safe_space;
                row.push_back(move(make_unique<Safe_Space>(safe_space)));
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
            x = rand() % game_dimension;
            y = rand() % game_dimension;

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
        int adjacent_bombs = completed_board[x][y]->get_adjacent_bombs();
        if (adjacent_bombs != -1) {
            adjacent_bombs++;
        }
        completed_board[x][y]->set_adjacent_bombs(adjacent_bombs);
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

};

#endif //PS_JV_GRAPHICS_FINAL_GAME_H
