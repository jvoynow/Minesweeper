#ifndef PS_JV_GRAPHICS_FINAL_FLAG_H
#define PS_JV_GRAPHICS_FINAL_FLAG_H

#include "Tile.h"

#include <string>

class Flag : public Tile {
public:
    Flag() {
        int temp = column;
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
    }

    string tile_display() override {
        return ">";
    }

    void draw() const override {
        glColor3f(current_fill.r, current_fill.g, current_fill.b);
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
