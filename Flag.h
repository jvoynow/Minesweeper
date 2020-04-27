#ifndef PS_JV_GRAPHICS_FINAL_FLAG_H
#define PS_JV_GRAPHICS_FINAL_FLAG_H

#include "Tile.h"

#include <string>

class Flag : public Tile {
public:
    Flag() {
    }

    string tile_display() override {
        return ">";
    }

    void draw() const override {
        int temp = column;
        if (row % 2 == 0) {
            ++temp;
        }
        if (temp % 2 == 1) {
            glColor3f(colors[LIGHT_BROWN].r, colors[LIGHT_BROWN].g,colors[LIGHT_BROWN].b);
        } else {
            glColor3f(colors[DARK_BROWN].r, colors[DARK_BROWN].g,colors[DARK_BROWN].b);
        }
        glBegin(GL_QUADS);
        glVertex2i(x1, y1);
        glVertex2i(x2, y1);
        glVertex2i(x2, y2);
        glVertex2i(x1, y2);
        glEnd();


        // TODO: Draw Flag here

        unsigned char filler[] = "12";
        int num = 12;
        glColor3f(colors[SEVEN].r, colors[SEVEN].g, colors[SEVEN].b);
        glRasterPos2i(x1 + (0.5 * (x2 - x1)) - (0.5 * glutBitmapLength(GLUT_BITMAP_HELVETICA_18, filler)),
                      y1 + (0.5 * (y2 - y1)) + (0.75 * glutBitmapLength(GLUT_BITMAP_HELVETICA_18, filler)));
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<int>('0' + num));
        glEnd();
    }
};

#endif //PS_JV_GRAPHICS_FINAL_FLAG_H
