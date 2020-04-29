#ifndef PS_JV_GRAPHICS_FINAL_SELECTED_BOMB_H
#define PS_JV_GRAPHICS_FINAL_SELECTED_BOMB_H

#include "Tile.h"
#include "Graphics.h"

class Selected_bomb : public Tile {
public:
    Selected_bomb() {
        adj_bombs = -1;
    }

    void draw() const override {
        // TODO: Change this
        glColor3f(current_fill.r,current_fill.g,current_fill.b);
        glBegin(GL_QUADS);
        glVertex2i(x1, y1);
        glVertex2i(x2, y1);
        glVertex2i(x2, y2);
        glVertex2i(x1, y2);
        glEnd();


        // TODO: Draw Bomb here
        unsigned char filler[] = "10";
        int num = 10;
        glColor3f(0,0,0);
        glRasterPos2i(x1 + (0.5 * (x2 - x1)) - (0.5 * glutBitmapLength(GLUT_BITMAP_HELVETICA_18, filler)),
                      y1 + (0.5 * (y2 - y1)) + (0.75 * glutBitmapLength(GLUT_BITMAP_HELVETICA_18, filler)));
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<int>('0' + num));
        glEnd();
    }
};

#endif //PS_JV_GRAPHICS_FINAL_SELECTED_BOMB_H
