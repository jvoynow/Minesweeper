#include "Graphics.h"
#include <iostream>
#include <vector>

using namespace std;

GLdouble width, height, padding;
int num_columns = 0, num_rows = 0, moves = 0;
int wd;
Button easy, intermediate, expert, main_menu;
vector<vector<unique_ptr<Tile>>> completed_board = create_board(false); // master board data/info
vector<vector<unique_ptr<Tile>>> user_interface_board = create_board (true);// user sees this, starts empty
int bomb_count;
bool won, game_over;


void init() {
    width = 1240;
    height = 640;
    padding = 300;
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(colors[MENU_BACKGROUND].r, colors[MENU_BACKGROUND].g, colors[MENU_BACKGROUND].b, 1.0f);
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // Tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height); // DO NOT CHANGE THIS LINE

    // Do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION); // DO NOT CHANGE THIS LINE
    glLoadIdentity(); // DO NOT CHANGE THIS LINE
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f); // DO NOT CHANGE THIS LINE

    // Clear the color buffer with current clearing color
    glClear(GL_COLOR_BUFFER_BIT); // DO NOT CHANGE THIS LINE

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // DO NOT CHANGE THIS LINE


    title();


/*    vector<unique_ptr<Tile>> tiles;


    Unselected_tile tile;
    tile.set_x1(400);
    tile.set_x2(600);
    tile.set_y1(100);
    tile.set_y2(300);
    tiles.push_back(make_unique<Unselected_tile>(tile));

    Unselected_flag flag;
    flag.set_x1(600);
    flag.set_x2(800);
    flag.set_y1(100);
    flag.set_y2(300);
    tiles.push_back(make_unique<Unselected_flag>(flag));



// TODO: SET coords before push_back

    Selected_bomb bomb;
    tiles.push_back(make_unique<Selected_bomb>(bomb));
    bomb.set_x1(400);
    bomb.set_x2(600);
    bomb.set_y1(300);
    bomb.set_y2(500);

    Selected_safe safe;
    tiles.push_back(make_unique<Selected_safe>(safe));
    safe.set_x1(600);
    safe.set_x2(800);
    safe.set_y1(300);
    safe.set_y2(500);

    for (unique_ptr<Tile> &tile : tiles) {
        tile->draw();
    }*/


    if (num_rows == 0 && num_columns == 0) {
        create_difficulty_buttons();
    } else {
        create_main_menu_button();
        // TODO: Fix play

        double x = padding, y = 0;
        double h = (height) / num_rows;
        double w = (width - padding) / num_columns;

        if (moves == 0) {
            for (int row = 0; row < num_rows; row++) {
                for (int col = 0; col < num_columns; col++) {
                    int temp = col;
                    if (row % 2 == 0) {
                        ++temp;
                    }
                    if (temp % 2 == 1) {
                        glColor3f(colors[LIGHT_GREEN].r, colors[LIGHT_GREEN].g,colors[LIGHT_GREEN].b);
                    } else {
                        glColor3f(colors[DARK_GREEN].r, colors[DARK_GREEN].g,colors[DARK_GREEN].b);
                    }
                    glBegin(GL_QUADS);
                    glVertex2i(x, y);
                    glVertex2i(x + w, y);
                    glVertex2i(x + w, y + h);
                    glVertex2i(x, y + h);
                    glEnd();
                    x += w;
                }
                x = padding;
                y += h;
            }
        } else {
            for (vector<unique_ptr<Tile>> &row_tiles : user_interface_board) {
                for (unique_ptr<Tile> &tile : row_tiles) {
                    tile->draw();
                }
            }
        }
    }

    display_creators();

    glFlush();  // Render now
}

void create_main_menu_button() {
    unsigned char menu[] = "MAIN MENU";
    if (main_menu.get_text() != "MAIN MENU") {
        main_menu.set_current_fill({colors[WHITE].r, colors[WHITE].g, colors[WHITE].b});
        main_menu.set_original_fill({colors[WHITE].r, colors[WHITE].g, colors[WHITE].b});
        main_menu.set_hover_fill({colors[WHITE_HOVER].r, colors[WHITE_HOVER].g, colors[WHITE_HOVER].b});
        main_menu.set_x1(
                (((double) padding / 2 - ((double) (glutBitmapLength(GLUT_BITMAP_HELVETICA_18, menu)) / 2)) - 30));
        main_menu.set_x2(
                (((double) padding / 2 + ((double) (glutBitmapLength(GLUT_BITMAP_HELVETICA_18, menu)) / 2)) + 30));
        main_menu.set_y1(((double) height - 100));
        main_menu.set_y2(((double) height - 64));
        main_menu.set_text("MAIN MENU");
    }
    main_menu.draw(padding, glutBitmapLength(GLUT_BITMAP_HELVETICA_18, menu));
}

void create_difficulty_buttons() {
    unsigned char easy_chars[] = "EASY";
    unsigned char intermediate_chars[] = "INTERMEDIATE";
    unsigned char expert_chars[] = "EXPERT";
    if (easy.get_text() != "EASY") {
        easy.set_current_fill({colors[WHITE].r, colors[WHITE].g, colors[WHITE].b});
        easy.set_original_fill({colors[WHITE].r, colors[WHITE].g, colors[WHITE].b});
        easy.set_hover_fill({colors[WHITE_HOVER].r, colors[WHITE_HOVER].g, colors[WHITE_HOVER].b});
        easy.set_x1((((double) padding / 2 -
                      ((double) (glutBitmapLength(GLUT_BITMAP_HELVETICA_18, intermediate_chars)) / 2)) - 10));
        easy.set_x2((((double) padding / 2 +
                      ((double) (glutBitmapLength(GLUT_BITMAP_HELVETICA_18, intermediate_chars)) / 2)) + 10));
        easy.set_y1((((double) height / 2) - 106));
        easy.set_y2((((double) height / 2) - 70));
        easy.set_text("EASY");
    }
    if (intermediate.get_text() != "INTERMEDIATE") {
        intermediate.set_current_fill({colors[WHITE].r, colors[WHITE].g, colors[WHITE].b});
        intermediate.set_original_fill({colors[WHITE].r, colors[WHITE].g, colors[WHITE].b});
        intermediate.set_hover_fill({colors[WHITE_HOVER].r, colors[WHITE_HOVER].g, colors[WHITE_HOVER].b});
        intermediate.set_x1((((double) padding / 2 -
                              ((double) (glutBitmapLength(GLUT_BITMAP_HELVETICA_18, intermediate_chars)) / 2)) - 10));
        intermediate.set_x2((((double) padding / 2 +
                              ((double) (glutBitmapLength(GLUT_BITMAP_HELVETICA_18, intermediate_chars)) / 2)) + 10));
        intermediate.set_y1((((double) height / 2) - 66));
        intermediate.set_y2((((double) height / 2) - 26));
        intermediate.set_text("INTERMEDIATE");
    }

    if (expert.get_text() != "EXPERT") {
        expert.set_current_fill({colors[WHITE].r, colors[WHITE].g, colors[WHITE].b});
        expert.set_original_fill({colors[WHITE].r, colors[WHITE].g, colors[WHITE].b});
        expert.set_hover_fill({colors[WHITE_HOVER].r, colors[WHITE_HOVER].g, colors[WHITE_HOVER].b});
        expert.set_x1((((double) padding / 2 -
                        ((double) (glutBitmapLength(GLUT_BITMAP_HELVETICA_18, intermediate_chars)) / 2)) - 10));
        expert.set_x2((((double) padding / 2 +
                        ((double) (glutBitmapLength(GLUT_BITMAP_HELVETICA_18, intermediate_chars)) / 2)) + 10));
        expert.set_y1((((double) height / 2) - 22));
        expert.set_y2((((double) height / 2) + 14));
        expert.set_text("EXPERT");
    }

    easy.draw(padding, glutBitmapLength(GLUT_BITMAP_HELVETICA_18, easy_chars));
    intermediate.draw(padding, glutBitmapLength(GLUT_BITMAP_HELVETICA_18, intermediate_chars));
    expert.draw(padding, glutBitmapLength(GLUT_BITMAP_HELVETICA_18, expert_chars));
}


void title() {
    unsigned char title[] = "Minesweeper";
    int w = glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, title);
    glRasterPos2i((double) padding / 2 - (double) w / 2, 60);
    glColor3f(colors[BLACK].r, colors[BLACK].g, colors[BLACK].b);
    for (char c : title) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
}

void display_creators() {
    unsigned char opening[] = "Created by:", parker[] = "Parker Strawbridge", sep[] = "&", jamie[] = "Jamie Voynow";
    int w = glutBitmapLength(GLUT_BITMAP_HELVETICA_10, opening);
    glColor3f(colors[BLACK].r, colors[BLACK].g, colors[BLACK].b);
    glRasterPos2i(double(padding) / 5 - (double) w / 2, height - 22);
    for (char c : opening) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    w = glutBitmapLength(GLUT_BITMAP_HELVETICA_10, parker);
    glRasterPos2i(double(padding) / 2 - (double) w / 2, height - 36);
    for (char c : parker) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    w = glutBitmapLength(GLUT_BITMAP_HELVETICA_10, sep);
    glRasterPos2i(double(padding) / 2 - (double) w / 2, height - 22);
    for (char c : sep) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    w = glutBitmapLength(GLUT_BITMAP_HELVETICA_10, jamie);
    glRasterPos2i(double(padding) / 2 - (double) w / 2, height - 8);
    for (char c : jamie) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
}


void kbd(unsigned char key, int x, int y) {
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }
    glutPostRedisplay();
}

void cursor(int x, int y) {
    if (easy.is_overlapping(x, y)) {
        easy.hover();
    } else {
        easy.stop_hover();
    }
    if (intermediate.is_overlapping(x, y)) {
        intermediate.hover();
    } else {
        intermediate.stop_hover();
    }
    if (expert.is_overlapping(x, y)) {
        expert.hover();
    } else {
        expert.stop_hover();
    }
    if (main_menu.is_overlapping(x, y)) {
        main_menu.hover();
    } else {
        main_menu.stop_hover();
    }

    for (vector<unique_ptr<Tile>> &row_tiles : user_interface_board) {
        for (unique_ptr<Tile> &tile : row_tiles) {
            if (tile->is_overlapping(x, y)) {
                tile->hover();
            } else {
                tile->stop_hover();
            }
        }
    }

    glutPostRedisplay();
}


// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (easy.is_overlapping(x, y) && num_rows == 0 && num_columns == 0) {
            num_rows = 8;
            num_columns = 8;
            bomb_count = 10;
            moves = 0;
        } else if (intermediate.is_overlapping(x, y) && num_rows == 0 && num_columns == 0) {
            num_rows= 16;
            num_columns = 16;
            bomb_count = 40;
            moves = 0;
        } else if (expert.is_overlapping(x, y) && num_rows == 0 && num_columns == 0) {
            num_rows= 16;
            num_columns = 30;
            bomb_count = 99;
            moves = 0;
        } else if (main_menu.is_overlapping(x, y) && num_rows != 0 && num_columns != 0) {
            num_columns = 0;
            num_rows = 0;
            bomb_count = 0;
            moves = 0;
        } else { // TODO: If not won or game over
            for (vector<unique_ptr<Tile>> &row_tiles : user_interface_board) {
                for (unique_ptr<Tile> &tile : row_tiles) {
                    if (tile->is_overlapping(x, y)) {
                        if (moves == 0) {
                            add_bombs(tile->get_row(), tile->get_column());
                            click_user_board(tile->get_row(), tile->get_column());

                            moves++;
                        } else {
                            click_user_board(tile->get_row(), tile->get_column());
                        }
                    }
                }
            }
        }

    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && !game_over && !won) {
        for (vector<unique_ptr<Tile>> &row_tiles : user_interface_board) {
            for (unique_ptr<Tile> &tile : row_tiles) {
                if (tile->is_overlapping(x, y)) {
                    flag_user_board(tile->get_row(), tile->get_column());
                }
            }
        }
    }

    glutPostRedisplay();
}

void timer(int dummy) {

    glutPostRedisplay();
    glutTimerFunc(30, timer, dummy);
}

void update_safe_spaces(int x, int y) {
    int adjacent_bombs = completed_board[x][y]->get_adj_bombs();
    if (adjacent_bombs != -1) {
        adjacent_bombs++;
    }
    completed_board[x][y]->set_adj_bombs(adjacent_bombs);
}

void update_safe_spaces_helper(int x, int y) {
    int row_out_of_bounds = num_rows - 1;
    int col_out_of_bounds = num_columns - 1;

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

void add_bombs(int row, int col) {
    vector<vector<int>> invalid_positions = get_invalid_positions(row, col);

    srand(time(nullptr));
    int x; // row
    int y; // column

    for (int i = 0; i < bomb_count; ++i) {
        while (true) {

            bool found = false;
            x = rand() % num_rows;
            y = rand() % num_columns;

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

            bomb.set_x1(padding + ((row - 1)* ((width - padding)/ num_columns)));
            bomb.set_x2(padding + (row * ((width - padding)/ num_columns)));
            bomb.set_y1((col - 1) * (height)/ num_rows);
            bomb.set_y2(col * (height)/ num_rows);

            bomb.set_current_fill(current_fill);
            bomb.set_original_fill(original_fill);
            bomb.set_hover_fill(hover_fill);

            unique_ptr<Selected_bomb> unique_bomb_ptr = make_unique<Selected_bomb>(bomb);
            completed_board[x][y] = move(unique_bomb_ptr);
            update_safe_spaces_helper(x, y);
        }
    }
}

vector<vector<unique_ptr<Tile>>> create_board(bool blank) {
    vector<vector<unique_ptr<Tile>>> new_board;
    color current_fill, original_fill, hover_fill;
    for (int y = 0; y < num_rows; ++y) {
        vector<unique_ptr<Tile>> row;
        for (int x = 0; x < num_columns; ++x) {
            if (blank) {
                Unselected_tile unselected;
                int temp = x;
                if (y % 2 == 0) {
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

                unselected.set_x1(padding + (x * ((width - padding)/ num_columns)));
                unselected.set_x2(padding + ((x + 1) * ((width - padding)/ num_columns)));
                unselected.set_y1(y * (height)/ num_rows);
                unselected.set_y2((y + 1) * (height)/ num_rows);

                row.push_back(move(make_unique<Unselected_tile>(unselected)));
            } else {
                Selected_safe space;

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

                space.set_x1(padding + (x * ((width - padding)/ num_columns)));
                space.set_x2(padding + ((x + 1) * ((width - padding)/ num_columns)));
                space.set_y1(y * (height)/ num_rows);
                space.set_y2((y + 1) * (height)/ num_rows);

                space.set_current_fill(current_fill);
                space.set_original_fill(original_fill);
                space.set_hover_fill(hover_fill);

                row.push_back(move(make_unique<Selected_safe>(space)));
            }
        }
        new_board.push_back(move(row));
    }
    return new_board;
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

void zero_search(int row, int col, vector<vector<int>> &coords) {
    if (row > num_rows - 1 or col > num_columns - 1 or row < 0 or col < 0) {
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

void click_user_board(int row, int col) {
    if (completed_board[row][col]->get_adj_bombs() == -1) {
        user_interface_board[row][col] = move(completed_board[row][col]);
        game_over = true;
    } else {
        vector<vector<int>> coords;
        zero_search(row, col, coords);
    }
}

void flag_user_board(int row, int col) {
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


    flag.set_x1(padding + ((row - 1)* ((width - padding)/ num_columns)));
    flag.set_x2(padding + (row * ((width - padding)/ num_columns)));
    flag.set_y1((col - 1) * (height)/ num_rows);
    flag.set_y2(col * (height)/ num_rows);

    flag.set_current_fill(current_fill);
    flag.set_original_fill(original_fill);
    flag.set_hover_fill(hover_fill);
    user_interface_board[row][col] = move(make_unique<Unselected_flag>(flag));
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {

    glutInit(&argc, argv);          // Initialize GLUT
    init();


    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(0, 0);
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Minesweeper");

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    glutKeyboardFunc(kbd);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);

    // handles timer
    glutTimerFunc(0, timer, 0);

    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}

