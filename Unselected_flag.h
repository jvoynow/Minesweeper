#ifndef PS_JV_GRAPHICS_FINAL_UNSELECTED_FLAG_H
#define PS_JV_GRAPHICS_FINAL_UNSELECTED_FLAG_H

#include "Tile.h"
#include "Graphics.h"

class Unselected_flag : public Tile {
public:
    Unselected_flag() = default;

    void draw() const override {
        // TODO: Change this
        //glColor3f(current_fill.r,current_fill.g,current_fill.b);
        glColor3f(1,0,0);
        glBegin(GL_QUADS);
        glVertex2i(x1, y1);
        glVertex2i(x2, y1);
        glVertex2i(x2, y2);
        glVertex2i(x1, y2);
        glEnd();



//        //flag
//        glColor3f(1,0,0);
//        glBegin(GL_TRIANGLES);
//        glVertex2i(x2 + 40, y1 + 20);
//        glVertex2i(x2 + 40, y1 + 60);
//        glVertex2i(x2 + 10, y1 + 40);
//        glEnd();
    }
};

#endif //PS_JV_GRAPHICS_FINAL_UNSELECTED_FLAG_H
