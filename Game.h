#ifndef PS_JV_GRAPHICS_FINAL_GAME_H
#define PS_JV_GRAPHICS_FINAL_GAME_H

#include "Selected_bomb.h"
#include "Selected_safe.h"
#include "Tile.h"
#include "Unselected_flag.h"
#include "Unselected_tile.h"

#include <ctime>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class Game {

private:
    vector<vector<unique_ptr<Tile>>> completed_board; // master board data/info
    vector<vector<unique_ptr<Tile>>> user_interface_board; // user sees this, starts empty
    vector<vector<int>> coords;
    int num_rows, num_cols, bomb_count, steps_until_win, moves;
    bool win, game_over;

public:

    Game() {
        win = false;
        game_over = false;
        moves = 0;
    }

    int get_steps_until_win() const {
        return steps_until_win;
    }

    bool get_game_over() {
        return game_over;
    }

    bool get_win() {
        return win;
    }

    // new game or reset game
    void update_game_members(int num_rows, int num_cols, int bomb_count) {
        this->num_rows = num_rows;
        this->num_cols = num_cols;
        this->bomb_count = bomb_count;
        steps_until_win = num_rows * num_cols - bomb_count;
    }

    // left  click logic
    void left_click(int pixel_x, int pixel_y, int padding, int width, int height) {
        for (vector<unique_ptr<Tile>> &row_tiles : user_interface_board) {
            for (unique_ptr<Tile> &tile : row_tiles) {
                if (tile->is_overlapping(pixel_x, pixel_y)) {
                    if (!exists_in_history(tile->get_row(), tile->get_column())) {
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
    }

    // helper function for left click edit board
    void click_user_board(int row, int col) {
        if (completed_board[row][col]->get_adj_bombs() == -1) {
            user_interface_board[row][col] = move(completed_board[row][col]);
            game_over = true;
        } else {
            zero_search(row, col);
        }
    }

    // called for right click -> flag
    void flag(int pixel_x, int pixel_y, int padding, int width, int height) {
        for (vector<unique_ptr<Tile>> &row_tiles : user_interface_board) {
            for (unique_ptr<Tile> &tile : row_tiles) {
                if (tile->is_overlapping(pixel_x, pixel_y)) {
                    flag_user_board(tile->get_row(), tile->get_column(), padding, width, height);
                }
            }
        }
    }

    // helper function to display flag correctly
    void flag_user_board(int row, int col, int padding, int width, int height) {
        color current_fill, original_fill, hover_fill;
        int temp = col;
        if (row % 2 == 0) {
            ++temp;
        }
        if ((user_interface_board[row][col]->get_adj_bombs() < 0 || user_interface_board[row][col]->get_adj_bombs() > 8)) {
            if (user_interface_board[row][col]->get_flagged()) {
                Unselected_tile unselected;
                if (temp % 2 == 1) {
                    original_fill = {colors[LIGHT_GREEN].r, colors[LIGHT_GREEN].g, colors[LIGHT_GREEN].b};
                    current_fill = {colors[LIGHT_GREEN].r, colors[LIGHT_GREEN].g, colors[LIGHT_GREEN].b};
                } else {
                    original_fill = {colors[DARK_GREEN].r, colors[DARK_GREEN].g, colors[DARK_GREEN].b};
                    current_fill = {colors[DARK_GREEN].r, colors[DARK_GREEN].g, colors[DARK_GREEN].b};
                }

                hover_fill = {colors[GREEN_HOVER].r, colors[GREEN_HOVER].g, colors[GREEN_HOVER].b};

                unselected.set_current_fill(current_fill);
                unselected.set_original_fill(original_fill);
                unselected.set_hover_fill(hover_fill);

                unselected.set_c1(padding + (col * ((width - padding) / num_cols)));
                unselected.set_c2(padding + ((col + 1) * ((width - padding) / num_cols)));
                unselected.set_r1(row * (height) / num_rows);
                unselected.set_r2((row + 1) * (height) / num_rows);

                unselected.set_row(row);
                unselected.set_column(col);
                user_interface_board[row][col] = move(make_unique<Unselected_tile>(unselected));

            } else {
                Unselected_flag flag;
                if (temp % 2 == 1) {
                    original_fill = {colors[LIGHT_GREEN].r, colors[LIGHT_GREEN].g, colors[LIGHT_GREEN].b};
                    current_fill = {colors[LIGHT_GREEN].r, colors[LIGHT_GREEN].g, colors[LIGHT_GREEN].b};
                } else {
                    original_fill = {colors[DARK_GREEN].r, colors[DARK_GREEN].g, colors[DARK_GREEN].b};
                    current_fill = {colors[DARK_GREEN].r, colors[DARK_GREEN].g, colors[DARK_GREEN].b};
                }

                hover_fill = {colors[GREEN_HOVER].r, colors[GREEN_HOVER].g, colors[GREEN_HOVER].b};

                flag.set_c1(padding + (col * ((width - padding) / num_cols)));
                flag.set_c2(padding + ((col + 1) * ((width - padding) / num_cols)));
                flag.set_r1((row) * (height) / num_rows);
                flag.set_r2((row + 1) * (height) / num_rows);


                flag.set_current_fill(current_fill);
                flag.set_original_fill(original_fill);
                flag.set_hover_fill(hover_fill);

                flag.set_row(row);
                flag.set_column(col);
                user_interface_board[row][col] = move(make_unique<Unselected_flag>(flag));
            }
        }

    }

    // logic for tile with zero adjacent bombs
    void zero_search(int row, int col) {
        // base case: out of bounds
        if (row > num_rows - 1 or col > num_cols - 1 or row < 0 or col < 0) {
            return;
        }

        // base case: previously searched
        if (exists_in_history(row, col)) {
            return;
        } else {
            coords.push_back({row, col});
        }

        // recursive calls for neighbors
        if (completed_board[row][col]->get_adj_bombs() == 0) {
            zero_search(row, col + 1);
            zero_search(row, col - 1);
            zero_search(row + 1, col);
            zero_search(row + 1, col + 1);
            zero_search(row + 1, col - 1);
            zero_search(row - 1, col);
            zero_search(row - 1, col + 1);
            zero_search(row - 1, col - 1);
        }
        // update users board
        user_interface_board[row][col] = move(completed_board[row][col]);
        --steps_until_win;
    }

    // look for tile in search history
    bool exists_in_history(int row, int col) {
        bool exists = false;
        for (int i = 0; i < coords.size(); ++i) {
            if (coords[i][0] == row and coords[i][1] == col) {
                exists = true;
            }
        }
        return exists;
    }

    // initialize bomb positions (disjoint from 3x3 set of tiles around row, col)
    void add_bombs(int row, int col, int padding, int width, int height) {
        vector<vector<int>> invalid_positions = get_invalid_positions(row, col);

        srand(time(nullptr));
        int x;
        int y;

        // loop through desired number of bomb
        for (int i = 0; i < bomb_count; ++i) {
            // access x, y by memory address and populate valid position
           get_valid_bomb_position(x, y, invalid_positions);

            Selected_bomb bomb;

            color current_fill, original_fill, hover_fill;
            int temp = x;
            if (y % 2 == 0) {
                ++temp;
            }
            if (temp % 2 == 1) {
                original_fill = {colors[LIGHT_BROWN].r, colors[LIGHT_BROWN].g,colors[LIGHT_BROWN].b};
                current_fill = {colors[LIGHT_BROWN].r, colors[LIGHT_BROWN].g,colors[LIGHT_BROWN].b};
            } else {
                original_fill = {colors[DARK_BROWN].r, colors[DARK_BROWN].g,colors[DARK_BROWN].b};
                current_fill = {colors[DARK_BROWN].r, colors[DARK_BROWN].g,colors[DARK_BROWN].b};
            }

            hover_fill = {colors[BROWN_HOVER].r, colors[BROWN_HOVER].g,colors[BROWN_HOVER].b};

            bomb.set_c1(padding + (y * ((width - padding)/ num_cols)));
            bomb.set_c2(padding + ((y + 1 )* ((width - padding)/ num_cols)));
            bomb.set_r1(x * (height)/ num_rows);
            bomb.set_r2((x + 1) * (height)/ num_rows);

            bomb.set_current_fill(current_fill);
            bomb.set_original_fill(original_fill);
            bomb.set_hover_fill(hover_fill);

//            bomb.set_row(row);
//            bomb.set_column(col);
            // update board with newly created bomb
            unique_ptr<Selected_bomb> unique_bomb_ptr = make_unique<Selected_bomb>(bomb);
            completed_board[x][y] = move(unique_bomb_ptr);
            update_safe_spaces_helper(x, y);
        }
    }

    // valid random x, y for bomb placement
    void get_valid_bomb_position(int &x, int &y, vector<vector<int>> invalid_positions) {
        // infinite loop until bomb position is valid
        while (true) {

            bool found = false;
            x = rand() % num_rows;
            y = rand() % num_cols;

            // search for x, y validity
            for (vector<int> &coord : invalid_positions) {
                if (coord[0] == x and coord[1] == y) {
                    found = true;
                }
            }
            // if valid, break infinite loop
            if (!found && completed_board[x][y]->get_adj_bombs() != -1) {
                break;
            }
        }
    }

    // accesses 3x3 set of surrounding tiles from a given position
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

    // helper function to increment adjacent bomb values for appropriate tiles
    void update_safe_spaces_helper(int x, int y) {
        int row_out_of_bounds = num_rows - 1;
        int col_out_of_bounds = num_cols - 1;

        // edge cases for top three adjacent positions
        if (x > 0) {
            // y = 0 edge case
            if (y > 0) {
                update_safe_spaces(x - 1, y - 1);
            }
            // y = num_cols edge case
            if (y < col_out_of_bounds) {
                update_safe_spaces(x - 1, y + 1);
            }
            update_safe_spaces(x - 1, y);
        }

        // edge cases for bottom three adjacent positions
        if (x < row_out_of_bounds) {
            // y = num_cols edge case
            if (y < col_out_of_bounds) {
                update_safe_spaces(x + 1, y + 1);
            }
            // y = 0 edge case
            if (y > 0) {
                update_safe_spaces(x + 1, y - 1);
            }
            update_safe_spaces(x + 1, y);
        }

        // edge cases for left and right adjacent positions
        if (y < col_out_of_bounds) {
            update_safe_spaces(x, y + 1);
        }
        if (y > 0) {
            update_safe_spaces(x, y - 1);
        }
    }

    // increment adjacent bombs for given tile at coordinates x, y
    void update_safe_spaces(int x, int y) {
        int adjacent_bombs = completed_board[x][y]->get_adj_bombs();
        if (adjacent_bombs != -1) {
            adjacent_bombs++;
        }
        completed_board[x][y]->set_adj_bombs(adjacent_bombs);
    }

    // initialization of the two boards
    void create_board_helper(int padding, int width, int height) {
        // completed used as reference for lookup when user clicks
        completed_board = create_board(false, padding, width, height);
        // user_interface used as what the user sees when playing game
        user_interface_board = create_board (true, padding, width, height);

        // re-initialization of members for new game functionality
        coords = {};
        moves = 0;
        game_over = false;
        win = false;
    }

    // populate boards with Tile objects
    vector<vector<unique_ptr<Tile>>> create_board(bool blank, int padding, int width, int height) {
        vector<vector<unique_ptr<Tile>>> new_board;
        color current_fill, original_fill, hover_fill;

        // row loop in range num_rows
        for (int row = 0; row < num_rows; ++row) {
            // create new row to append Tile objects in range num_cols
            vector<unique_ptr<Tile>> row_vec;
            for (int col = 0; col < num_cols; ++col) {

                // create user interface board
                if (blank) {
                    Unselected_tile unselected;
                    int temp = col;
                    if (row % 2 == 0) {
                        ++temp;
                    }
                    if (temp % 2 == 1) {
                        original_fill = {colors[LIGHT_GREEN].r, colors[LIGHT_GREEN].g,colors[LIGHT_GREEN].b};
                        current_fill = {colors[LIGHT_GREEN].r, colors[LIGHT_GREEN].g,colors[LIGHT_GREEN].b};
                    } else {
                        original_fill = {colors[DARK_GREEN].r, colors[DARK_GREEN].g,colors[DARK_GREEN].b};
                        current_fill = {colors[DARK_GREEN].r, colors[DARK_GREEN].g,colors[DARK_GREEN].b};
                    }

                    hover_fill = {colors[GREEN_HOVER].r, colors[GREEN_HOVER].g,colors[GREEN_HOVER].b};

                    unselected.set_current_fill(current_fill);
                    unselected.set_original_fill(original_fill);
                    unselected.set_hover_fill(hover_fill);

                    unselected.set_c1(padding + (col * ((width - padding)/ num_cols)));
                    unselected.set_c2(padding + ((col + 1) * ((width - padding)/ num_cols)));
                    unselected.set_r1(row * (height)/ num_rows);
                    unselected.set_r2((row + 1) * (height)/ num_rows);

                    unselected.set_row(row);
                    unselected.set_column(col);

                    // add tile object to 1D row
                    row_vec.push_back(move(make_unique<Unselected_tile>(unselected)));

                // create completed board
                } else {
                    Selected_safe space;
                    int temp = col;
                    if (row % 2 == 0) {
                        ++temp;
                    }
                    if (temp % 2 == 1) {
                        original_fill = {colors[LIGHT_BROWN].r, colors[LIGHT_BROWN].g,colors[LIGHT_BROWN].b};
                        current_fill = {colors[LIGHT_BROWN].r, colors[LIGHT_BROWN].g,colors[LIGHT_BROWN].b};
                    } else {
                        original_fill = {colors[DARK_BROWN].r, colors[DARK_BROWN].g,colors[DARK_BROWN].b};
                        current_fill = {colors[DARK_BROWN].r, colors[DARK_BROWN].g,colors[DARK_BROWN].b};
                    }

                    hover_fill = {colors[BROWN_HOVER].r, colors[BROWN_HOVER].g,colors[BROWN_HOVER].b};

                    space.set_c1(padding + (col * ((width - padding)/ num_cols)));
                    space.set_c2(padding + ((col + 1) * ((width - padding)/ num_cols)));
                    space.set_r1(row * (height)/ num_rows);
                    space.set_r2((row + 1) * (height)/ num_rows);

                    space.set_current_fill(current_fill);
                    space.set_original_fill(original_fill);
                    space.set_hover_fill(hover_fill);

                    space.set_row(row);
                    space.set_column(col);

                    // add tile object to 1D row
                    row_vec.push_back(move(make_unique<Selected_safe>(space)));
                }
            }
            // add 1D row to 2D board
            new_board.push_back(move(row_vec));
        }
        return new_board;
    }

    void hover(int pixel_x, int pixel_y) {
        for (vector<unique_ptr<Tile>> &row_tiles : user_interface_board) {
            for (unique_ptr<Tile> &tile : row_tiles) {
                if (tile->is_overlapping(pixel_x, pixel_y)) {
                    tile->hover();
                } else {
                    tile->stop_hover();
                }
            }
        }
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
