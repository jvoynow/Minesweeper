#ifndef PS_JV_GRAPHICS_FINAL_UNSELECTED_FLAG_H
#define PS_JV_GRAPHICS_FINAL_UNSELECTED_FLAG_H

#include "Tile.h"
#include "Graphics.h"

class Unselected_flag : public Tile {
public:
    Unselected_flag() = default;

    void draw() const override {
        glColor3f(current_fill.r,current_fill.g,current_fill.b);
        glBegin(GL_QUADS);
        glVertex2i(c1, r1);
        glVertex2i(c2, r1);
        glVertex2i(c2, r2);
        glVertex2i(c1, r2);
        glEnd();

        // Pole
        glColor3f(0,0,0);
        glBegin(GL_QUADS);
        glVertex2i((c2 - c1) / 2 + c1 - 1.5, r1 + ((r2 - r1) / 4));
        glVertex2i((c2 - c1) / 2 + c1 - 1.5, r2 - ((r2 - r1) / 10));
        glVertex2i((c2 - c1) / 2 + c1 + 1.5, r2 - ((r2 - r1) / 10));
        glVertex2i((c2 - c1) / 2 + c1 + 1.5, r1 + ((r2 - r1) / 4));
        glEnd();

        // Base
        glColor3f(0,0,0);
        glBegin(GL_QUADS);
        glVertex2i((c2 - c1) / 2.5 + c1 , r2 - ((r2 - r1) / 6));
        glVertex2i((c2 - c1) / 2.5 + c1, r2 - ((r2 - r1) / 10));
        glVertex2i(c2 - ((c2 - c1) / 2.5), r2 - ((r2 - r1) / 10));
        glVertex2i(c2 - ((c2 - c1) / 2.5), r2 - ((r2 - r1) / 6));
        glEnd();

        // Flag
        glColor3f(1,0,0);
        glBegin(GL_TRIANGLES);
        glVertex2i((c2 - c1) / 2 + c1 - 1.5, r1 + ((r2 - r1) / 2));
        glVertex2i((c2 - c1) / 2 + c1 - 1.5, r1 + ((r2 - r1) / 6));
        glVertex2i(c2 - ((c2 - c1) / 10), r1 + ((r2 - r1) / 3));
        glEnd();
    }
};

#endif //PS_JV_GRAPHICS_FINAL_UNSELECTED_FLAG_H
