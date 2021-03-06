#include "Selected_safe.h"
#include "Graphics.h"

Selected_safe::Selected_safe() {
    adj_bombs = 0;
    flagged = false;
}

void Selected_safe::draw() const {
    // Draw tile
    glColor3f(current_fill.r,current_fill.g,current_fill.b);
    glBegin(GL_QUADS);
    glVertex2i(c1, r1);
    glVertex2i(c2, r1);
    glVertex2i(c2, r2);
    glVertex2i(c1, r2);
    glEnd();

    // If the tile does not have 0 adjacent bombs draw the number of adjacent bombs it has in the tile
    if (adj_bombs != 0) {
        glColor3f(0,0,0);
        unsigned char filler[] = "8";
        glRasterPos2i(c1 + (0.5 * (c2 - c1)) - (0.5 * glutBitmapLength(GLUT_BITMAP_HELVETICA_18, filler)),
                      r1 + (0.5 * (r2 - r1)) + (0.75 * glutBitmapLength(GLUT_BITMAP_HELVETICA_18, filler)));
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<int>('0' + adj_bombs));
        glEnd();
    }
}

