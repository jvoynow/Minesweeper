#ifndef PS_JV_GRAPHICS_FINAL_GAME_H
#define PS_JV_GRAPHICS_FINAL_GAME_H

#include "Bomb.h"
#include "Flag.h"
#include "Safe_Space.h"
#include "Tile.h"
#include "Unselected_tile.h"


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
    bool won, game_over;

public:
    Game(int num_rows, int num_cols, int bomb_count) {
        this->num_rows = num_rows;
        this->num_cols = num_cols;
        this->bomb_count = bomb_count;
        won = false;
        game_over = false;

        completed_board = create_board(false);
        user_interface_board = create_board(true);
    }

    bool is_won() const {
        return won;
    }

    bool is_over() const {
        return game_over;
    };

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


    vector<vector<unique_ptr<Tile>>> get_board() const {
        return user_interface_board;
    }

    void play() {
        int row = 0, col = 0;
        string input = "w";

        //print(user_interface_board, row, col);
        input = get_position(user_interface_board, row, col, input);
        add_bombs(row, col);

        while (input != "e" and input != "b") {
            input = update_board(user_interface_board, row, col, input);
            if (input != "b") {
                //print(user_interface_board, row, col);
                input = get_position(user_interface_board, row, col, input);
            }
        }

        //print(user_interface_board, row, col);
    }

    static string get_position(vector<vector<unique_ptr<Tile>>> &current_board, int &row, int &col, string input) {
        //cout << "Input move:";
        cin >> input;

        while (input != "c" and input !=  "f" and input != "e") {
            move_cursor(row, col, input);
            //print(current_board, row, col);
            //cout << "Input move:";
            cin >> input;
        }
        return input;
    }

    static void move_cursor(int &row, int &col, string &input) {
        if(input == "w") {row--;}
        if(input == "a") {col--;}
        if(input == "s") {row++;}
        if(input == "d") {col++;}
    }

    // Todo this is the logic for flagging
    void flag_user_board(int row, int col) {
        Flag flag;
        user_interface_board[row][col] = move(make_unique<Flag>(flag));
    }

    // Todo this is the logic for clicking on the board
    void click_user_board(int row, int col) {
        if (completed_board[row][col]->get_adj_bombs() == -1) {
            user_interface_board[row][col] = move(completed_board[row][col]);
        } else {
            vector<vector<int>> coords;
            zero_search(row, col, coords);
        }
    }

    void update_board_for_win() {
        for (int i = 0; i < num_rows; ++i) {
            for (int j = 0; j < num_cols; ++j) {

            }
        }
    }

    void zero_search(int row, int col, vector<vector<int>> &coords) {
        if (row > num_rows - 1 or col > num_cols - 1 or row < 0 or col < 0) {
            return;
        }
        if (exists_in_history(row, col, coords)) {
            return;
        } else {
            coords.push_back({row, col});
        }
        if (completed_board[row][col]->get_adj_bombs() == 0) {
            zero_search(row, col + 1, coords);
            zero_search(row, col - 1, coords);
            zero_search(row + 1, col, coords);
            zero_search(row + 1, col + 1, coords);
            zero_search(row + 1, col - 1, coords);
            zero_search(row - 1, col, coords);
            zero_search(row - 1, col + 1, coords);
            zero_search(row - 1, col - 1, coords);
        }
        user_interface_board[row][col] = move(completed_board[row][col]);
    }

    static bool exists_in_history(int row, int col, vector<vector<int>> coords) {
        bool exists = false;
        for (int i = 0; i < coords.size(); ++i) {
            if (coords[i][0] == row and coords[i][1] == col) {
                exists = true;
            }
        }

        return exists;
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

    void add_bombs(int row, int col) {
        vector<vector<int>> invalid_positions = get_invalid_positions(row, col);

        srand(time(nullptr));
        int x; // row
        int y; // column

        for (int i = 0; i < bomb_count; ++i) {
            while (true) {

                bool found = false;
                x = rand() % num_rows;
                y = rand() % num_cols;

                for (vector<int> &coord : invalid_positions) {
                    if (coord[0] == x and coord[1] == y) {
                        found = true;
                    }
                }
                if (!found) {
                    break;
                }
            }

            // check if bomb exists in given position
            if (completed_board[x][y]->get_adj_bombs() != -1) {
                Bomb bomb;
                unique_ptr<Bomb> unique_bomb_ptr = make_unique<Bomb>(bomb);
                completed_board[x][y] = move(unique_bomb_ptr);
                update_safe_spaces_helper(x, y);
            }
        }
    }

    static vector<vector<int>> get_invalid_positions(int row, int col) {
        vector<vector<int>> invalid_positions;
        invalid_positions.push_back({row, col});
        invalid_positions.push_back({row, col + 1});
        invalid_positions.push_back({row, col - 1});
        invalid_positions.push_back({row + 1, col + 1});
        invalid_positions.push_back({row + 1, col - 1});
        invalid_positions.push_back({row + 1, col});
        invalid_positions.push_back({row - 1, col + 1});
        invalid_positions.push_back({row - 1, col - 1});
        invalid_positions.push_back({row - 1, col});

        return invalid_positions;
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

/*    static void print(vector<vector<unique_ptr<Tile>>> &board, int row, int col) {
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[i].size(); ++j) {
                if (i == row && j == col) {
                    //cout << " |*" ;
                } else {
                    //cout << " | ";
                }
                //cout << board[i][j]->tile_display();
            }
            //cout << " |" << endl;
        }
        //cout << endl;
    }*/

};

#endif //PS_JV_GRAPHICS_FINAL_GAME_H
