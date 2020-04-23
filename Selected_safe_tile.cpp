#include "Selected_safe_tile.h"


using namespace std;


Selected_safe_tile::Selected_safe_tile() {
    row = 0;
    column = 0;
    adj_bombs = 0;
}

/*Selected_safe_tile::Selected_safe_tile(int row, int column, int adj_bombs) {
    this->row = row;
    this->column = column;
    this->adj_bombs = adj_bombs;
    int temp = column;
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
}*/

void Selected_safe_tile::set_adj_bombs(int adj_bombs) {
    this->adj_bombs = adj_bombs;
}


int Selected_safe_tile::get_adj_bombs() const {
    return adj_bombs;
}

/*void Selected_safe_tile::draw(double x, double y, double width, double height, int tile_width, int tile_height, double padding) const {
    glColor3f(current_fill.r, current_fill.g, current_fill.b);
    glBegin(GL_QUADS);
    glVertex2i( x + 0 * width, y + 0 * height);
    glVertex2i(x + 1 * width, y + 0 * height);
    glVertex2i(x + 1 * width, y + 1 * height);
    glVertex2i(x + 0 * width, y + 1 * height);
    glEnd();

    if (adj_bombs != 0) {
        Color num_string;
        unsigned char num_space_size[] = "8";
        if (adj_bombs == 1) {
            num_string = ONE;
        } else if (adj_bombs == 2) {
            num_string = TWO;
        } else if (adj_bombs == 3) {
            num_string = THREE;
        } else if (adj_bombs == 4) {
            num_string = FOUR;
        } else if (adj_bombs == 5) {
            num_string = FIVE;
        } else if (adj_bombs == 6) {
            num_string = SIX;
        } else if (adj_bombs == 7) {
            num_string = SEVEN;
        } else if (adj_bombs == 8) {
            num_string = EIGHT;
        }

        glColor3f(colors[num_string].r, colors[num_string].g, colors[num_string].b);
        glRasterPos2i(x + (0.5 * width) - (0.5 * glutBitmapLength(GLUT_BITMAP_HELVETICA_18, num_space_size)), y + (0.5 * height) + (0.75 * glutBitmapLength(GLUT_BITMAP_HELVETICA_18, num_space_size)));
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '0' + adj_bombs);
        glEnd();
    }
    }*/
