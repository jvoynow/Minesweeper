#ifndef PS_JV_GRAPHICS_FINAL_GAME_H
#define PS_JV_GRAPHICS_FINAL_GAME_H

#include "Tile.h"
#include "Graphics.h"
#include "Selected_bomb.h"
#include "Selected_safe.h"
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
    /**
     * Constructor
     */
    Game();

    /**
     * Getters
     */
    int get_steps_until_win() const;
    bool get_game_over();
    bool get_win();

    /**
     * Updates the fields of the game object (Glorified setter with three parameters)
     * @param num_rows
     * @param num_cols
     * @param bomb_count
     */
    void update_game_members(int num_rows, int num_cols, int bomb_count);

    /**
     * Determines if the mouse x, y location is on a tile
     * First move: calls click user board and adds bombs
     * All other moves: calls click user board
     * @param pixel_x: cursor x value
     * @param pixel_y: cursor y value
     * @param padding: menu padding
     * @param width: window width
     * @param height: window height
     */
    void left_click(int pixel_x, int pixel_y, int padding, int width, int height);

    /**
     * Moves the corresponding tile in the completed board to the user's board
     * @param row: row of tile clicked
     * @param col: column of tile clicked
     */
    void click_user_board(int row, int col);

    /**
     * Flags the tile at the given x,y coordinates
     * @param pixel_x: cursor x value
     * @param pixel_y: cursor y value
     * @param padding: menu padding
     * @param width: window width
     * @param height: window height
     */
    void flag(int pixel_x, int pixel_y, int padding, int width, int height);

    /**
     * Determines if a tile is being flagged or un-flagged and creates the correct tile object
     * Adds the new tile to the user's board
     * @param row: row of tile being flagged
     * @param col: column of tile being flagged
     * @param padding: menu padding
     * @param width: window width
     * @param height: window height
     */
    void flag_user_board(int row, int col, int padding, int width, int height);



    /**
     * Called upon the instance of a left click on a non-bomb tile.
     * Adds clicked tiles coordinates to a list or history of previously chosen tiles.
     * If tile has zero adjacent bombs, this function recursively calls zero_search on
     * all adjacent tiles to create a local set of tiles to display.
     * @param row: row of chosen tile
     * @param col: col of chosen tile
     */
    void zero_search(int row, int col);

    /**
     * Determines if a tile has already been searched for
     * @param row: row of tile being checked
     * @param col: column of tile being checked
     * @return true: if coordinates exist in the history, false if not
     */
    bool exists_in_history(int row, int col);

    /**
     * Adds bombs equal to the bomb count to the completed board in valid positions
     * @param row: row of first click
     * @param col: column of first click
     * @param padding: menu padding
     * @param width: window width
     * @param height: window height
     */
    void add_bombs(int row, int col, int padding, int width, int height);

    /**
     * Updates x, y coordinates for a random valid bomb location
     * @param x: row coordinate for bomb location
     * @param y: column coordinate for bomb location
     * @param invalid_positions: 2d vector of invalid bomb locations
     */
    void get_valid_bomb_position(int &x, int &y, vector<vector<int>> invalid_positions);

    /**
     * Populates and returns a 2D vector of invalid bomb loacations
     * @param row: Row of initial click
     * @param col: Column of initial click
     * @return 2D vector of invalid bomb positions
     */
    static vector<vector<int>> get_invalid_positions(int row, int col);

    /**
     * Helper function to increment adjacent bomb values
     * @param x: row value of tile in the board
     * @param y: column value of tile in the board
     */
    void update_safe_spaces_helper(int x, int y);

    /**
     * Increment adjacent bombs at the location x,y in the board
     * @param x: row value of tile in the board
     * @param y: column value of tile in the board
     */
    void update_safe_spaces(int x, int y);

    /**
     * Initializes both the user and completed board
     * Re-initialization of members for new game functionality
     * @param padding: menu padding
     * @param width: window width
     * @param height: window height
     */
    void create_board_helper(int padding, int width, int height);

    /**
     * Populates a board with unique pointers to tile objects
     * @param blank: true if user's board, false if completed board
     * @param padding: menu padding
     * @param width: window width
     * @param height: window height
     * @return 2D vector of unique pointers to Tile objects
     */
    vector<vector<unique_ptr<Tile>>> create_board(bool blank, int padding, int width, int height);

    /**
     * Handles the cursor hover affect for all tiles in the board
     * @param pixel_x: x value of cursor location
     * @param pixel_y: y value of cursor location
     */
    void hover(int pixel_x, int pixel_y);

    /**
     * Draws all tiles in the board using polymorphism
     */
    void draw();

    /**
     * Adds all bomb locations to the user's board to be displayed when the game has been lost
     * @param padding: menu padding
     * @param width: window width
     * @param height: window height
     */
    void lost_game(int padding, int width, int height);
};

#endif //PS_JV_GRAPHICS_FINAL_GAME_H
