#ifndef PS_JV_GRAPHICS_FINAL_GAME_H
#define PS_JV_GRAPHICS_FINAL_GAME_H

#include "Unselected_flag.h"
#include "Selected_safe.h"
#include "Selected_bomb.h"
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
    bool win, game_over;
    int steps_until_win, moves;

public:
//    Game() {
//
//    }
    Game() {
        win = false;
        game_over = false;
        moves = 0;
    }

    void update_game_members(int num_rows, int num_cols, int bomb_count) {
        this->num_rows = num_rows;
        this->num_cols = num_cols;
        this->bomb_count = bomb_count;
        steps_until_win = num_rows * num_cols - bomb_count;
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

    int get_moves() const {
        return moves;
    }

    bool get_game_over() {
        return game_over;
    }

    bool get_win() {
        return win;
    }

    void left_click(int pixel_x, int pixel_y, int padding, int width, int height) {
        for (vector<unique_ptr<Tile>> &row_tiles : user_interface_board) {
            for (unique_ptr<Tile> &tile : row_tiles) {
                if (tile->is_overlapping(pixel_x, pixel_y)) {
                    if (moves == 0) {
                        add_bombs(tile->get_row(), tile->get_column(), padding, width, height);
                        click_user_board(tile->get_row(), tile->get_column());
                    } else {
                        click_user_board(tile->get_row(), tile->get_column());
                    }
                    moves++;
                }
            }
        }
    }

    void flag(int pixel_x, int pixel_y, int padding, int width, int height) {
        for (vector<unique_ptr<Tile>> &row_tiles : user_interface_board) {
            for (unique_ptr<Tile> &tile : row_tiles) {
                if (tile->is_overlapping(pixel_x, pixel_y)) {
                    flag_user_board(tile->get_row(), tile->get_column(), padding, width, height);
                }
            }
        }
    }

    // Todo this is the logic for flagging
    void flag_user_board(int row, int col, int padding, int width, int height) {
        Unselected_flag flag;
        int temp = col;
        color current_fill, original_fill, hover_fill;
        if (row % 2 == 0) {
            ++temp;
        }
        if (temp % 2 == 1) {
            original_fill = {colors[LIGHT_GREEN].r, colors[LIGHT_GREEN].g,colors[LIGHT_GREEN].b};
            current_fill = {colors[LIGHT_GREEN].r, colors[LIGHT_GREEN].g,colors[LIGHT_GREEN].b};
            // TODO Change this
            hover_fill = {colors[DARK_GREEN].r, colors[DARK_GREEN].g,colors[DARK_GREEN].b};

        } else {
            original_fill = {colors[DARK_GREEN].r, colors[DARK_GREEN].g,colors[DARK_GREEN].b};
            current_fill = {colors[DARK_GREEN].r, colors[DARK_GREEN].g,colors[DARK_GREEN].b};
            // TODO Change this
            hover_fill = {colors[LIGHT_GREEN].r, colors[LIGHT_GREEN].g,colors[LIGHT_GREEN].b};
        }


        flag.set_x1(padding + (row * ((width - padding)/ num_cols)));
        flag.set_x2(padding + ((row + 1) * ((width - padding)/ num_cols)));
        flag.set_y1((col) * (height)/ num_rows);
        flag.set_y2((col + 1) * (height)/ num_rows);


        cout << row << " " << col << endl;

        flag.set_current_fill(current_fill);
        flag.set_original_fill(original_fill);
        flag.set_hover_fill(hover_fill);

        flag.set_row(row);
        flag.set_column(col);
        user_interface_board[row][col] = move(make_unique<Unselected_flag>(flag));
    }

    // Todo this is the logic for clicking on the board
    void click_user_board(int row, int col) {
        if (completed_board[row][col]->get_adj_bombs() == -1) {
            user_interface_board[row][col] = move(completed_board[row][col]);
            game_over = true;
        } else {
            vector<vector<int>> coords;
            zero_search(row, col, coords);
            --steps_until_win;
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

    void create_board_helper(int padding, int width, int height) {
        completed_board = create_board(false, padding, width, height);
        user_interface_board = create_board (true, padding, width, height);
    }

    vector<vector<unique_ptr<Tile>>> create_board(bool blank, int padding, int width, int height) {
        vector<vector<unique_ptr<Tile>>> new_board;
        color current_fill, original_fill, hover_fill;
        for (int row = 0; row < num_rows; ++row) {
            vector<unique_ptr<Tile>> row_vec;
            for (int col = 0; col < num_cols; ++col) {
                if (blank) {
                    Unselected_tile unselected;
                    int temp = col;
                    if (row % 2 == 0) {
                        ++temp;
                    }
                    if (temp % 2 == 1) {
                        original_fill = {colors[LIGHT_GREEN].r, colors[LIGHT_GREEN].g,colors[LIGHT_GREEN].b};
                        current_fill = {colors[LIGHT_GREEN].r, colors[LIGHT_GREEN].g,colors[LIGHT_GREEN].b};
                        // TODO Change this
                        hover_fill = {colors[DARK_GREEN].r, colors[DARK_GREEN].g,colors[DARK_GREEN].b};

                    } else {
                        original_fill = {colors[DARK_GREEN].r, colors[DARK_GREEN].g,colors[DARK_GREEN].b};
                        current_fill = {colors[DARK_GREEN].r, colors[DARK_GREEN].g,colors[DARK_GREEN].b};
                        // TODO Change this
                        hover_fill = {colors[LIGHT_GREEN].r, colors[LIGHT_GREEN].g,colors[LIGHT_GREEN].b};
                    }
                    unselected.set_current_fill(current_fill);
                    unselected.set_original_fill(original_fill);
                    unselected.set_hover_fill(hover_fill);

                    unselected.set_x1(padding + (row * ((width - padding)/ num_cols)));
                    unselected.set_x2(padding + ((row + 1) * ((width - padding)/ num_cols)));
                    unselected.set_y1(col * (height)/ num_rows);
                    unselected.set_y2((col + 1) * (height)/ num_rows);

                    unselected.set_row(row);
                    unselected.set_column(col);

                    row_vec.push_back(move(make_unique<Unselected_tile>(unselected)));
                } else {
                    Selected_safe space;

                    int temp = col;
                    if (row % 2 == 0) {
                        ++temp;
                    }
                    if (temp % 2 == 1) {
                        original_fill = {colors[LIGHT_BROWN].r, colors[LIGHT_BROWN].g,colors[LIGHT_BROWN].b};
                        current_fill = {colors[LIGHT_BROWN].r, colors[LIGHT_BROWN].g,colors[LIGHT_BROWN].b};
                        // TODO Change this
                        hover_fill = {colors[DARK_BROWN].r, colors[DARK_BROWN].g,colors[DARK_BROWN].b};
                    } else {
                        original_fill = {colors[DARK_BROWN].r, colors[DARK_BROWN].g,colors[DARK_BROWN].b};
                        current_fill = {colors[DARK_BROWN].r, colors[DARK_BROWN].g,colors[DARK_BROWN].b};
                        // TODO Change this
                        hover_fill = {colors[LIGHT_BROWN].r, colors[LIGHT_BROWN].g,colors[LIGHT_BROWN].b};
                    }

                    space.set_x1(padding + (row * ((width - padding)/ num_cols)));
                    space.set_x2(padding + ((row + 1) * ((width - padding)/ num_cols)));
                    space.set_y1(col * (height)/ num_rows);
                    space.set_y2((col + 1) * (height)/ num_rows);

                    space.set_current_fill(current_fill);
                    space.set_original_fill(original_fill);
                    space.set_hover_fill(hover_fill);

                    space.set_row(row);
                    space.set_column(col);

                    row_vec.push_back(move(make_unique<Selected_safe>(space)));
                }
            }
            new_board.push_back(move(row_vec));
        }
        return new_board;
    }

    void add_bombs(int row, int col, int padding, int width, int height) {
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
                Selected_bomb bomb;

                color current_fill, original_fill, hover_fill;
                int temp = x;
                if (y % 2 == 0) {
                    ++temp;
                }
                if (temp % 2 == 1) {
                    original_fill = {colors[LIGHT_BROWN].r, colors[LIGHT_BROWN].g,colors[LIGHT_BROWN].b};
                    current_fill = {colors[LIGHT_BROWN].r, colors[LIGHT_BROWN].g,colors[LIGHT_BROWN].b};
                    // TODO Change this
                    hover_fill = {colors[DARK_BROWN].r, colors[DARK_BROWN].g,colors[DARK_BROWN].b};
                } else {
                    original_fill = {colors[DARK_BROWN].r, colors[DARK_BROWN].g,colors[DARK_BROWN].b};
                    current_fill = {colors[DARK_BROWN].r, colors[DARK_BROWN].g,colors[DARK_BROWN].b};
                    // TODO Change this
                    hover_fill = {colors[LIGHT_BROWN].r, colors[LIGHT_BROWN].g,colors[LIGHT_BROWN].b};
                }

                bomb.set_x1(padding + (col * ((width - padding)/ num_cols)));
                bomb.set_x2(padding + ((col + 1 )* ((width - padding)/ num_cols)));
                bomb.set_y1(row * (height)/ num_rows);
                bomb.set_y2((row + 1) * (height)/ num_rows);

                bomb.set_current_fill(current_fill);
                bomb.set_original_fill(original_fill);
                bomb.set_hover_fill(hover_fill);

                bomb.set_row(row);
                bomb.set_column(col);
                unique_ptr<Selected_bomb> unique_bomb_ptr = make_unique<Selected_bomb>(bomb);
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

    void draw() {
        for (vector<unique_ptr<Tile>> &row_tiles : user_interface_board) {
            for (unique_ptr<Tile> &tile : row_tiles) {
                tile->draw();
            }
        }
    }
};

#endif //PS_JV_GRAPHICS_FINAL_GAME_H
