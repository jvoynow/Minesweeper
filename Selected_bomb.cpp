#include "Selected_bomb.h"
#include "Graphics.h"

Selected_bomb::Selected_bomb() : Tile() {
    adj_bombs = -1;
}

void Selected_bomb::draw() const {
    // Draw tile
    glColor3f(current_fill.r, current_fill.g, current_fill.b);
    glBegin(GL_QUADS);
    glVertex2i(c1, r1);
    glVertex2i(c2, r1);
    glVertex2i(c2, r2);
    glVertex2i(c1, r2);
    glEnd();

    // Draw spikes
    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2i((c2 - c1) / 2 + 1.5 + c1, (r2 - r1) / 6 + r1);
    glVertex2i((c2 - c1) / 2 - 1.5 + c1, (r2 - r1) / 6 + r1);
    glVertex2i((c2 - c1) / 2 - 1.5 + c1, r2 - ((r2 - r1) / 6));
    glVertex2i((c2 - c1) / 2 + 1.5 + c1, r2 - ((r2 - r1) / 6));
    glEnd();

    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2i((c2 - c1) / 4 + c1, (r2 - r1) / 2 + 1.5 + r1);
    glVertex2i(c2 - ((c2 - c1) / 4), (r2 - r1) / 2 + 1.5 + r1);
    glVertex2i(c2 - ((c2 - c1) / 4), (r2 - r1) / 2 - 1.5 + r1);
    glVertex2i((c2 - c1) / 4 + c1, (r2 - r1) / 2 - 1.5 + r1);
    glEnd();


    // Draw "circle"
    glColor3f(0, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2i((c2 - c1) / 2 + c1, (r2 - r1) / 2 + r1);

    glVertex2i((c2 - c1) / 2 + c1, (r2 - r1) / 4 + r1);
    glVertex2i((c2 - c1) / 2.5 + c1, (r2 - r1) / 3 + r1);
    glVertex2i((c2 - c1) / 3 + c1, (r2 - r1) / 2 + r1);
    glVertex2i((c2 - c1) / 2.5 + c1, r2 - ((r2 - r1) / 3));
    glVertex2i((c2 - c1) / 2 + c1, r2 - ((r2 - r1) / 4));
    glVertex2i(c2 - ((c2 - c1) / 2.5), r2 - ((r2 - r1) / 3));
    glVertex2i(c2 - ((c2 - c1) / 3), (r2 - r1) / 2 + r1);
    glVertex2i(c2 - ((c2 - c1) / 2.5), (r2 - r1) / 3 + r1);
    glVertex2i((c2 - c1) / 2 + c1, (r2 - r1) / 4 + r1);
    glEnd();

    // Draw square shine
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_QUADS);
    glVertex2i((c2 - c1) / 2.3 + c1, (r2 - r1) / 2.5 + r1);
    glVertex2i((c2 - c1) / 2 + c1, (r2 - r1) / 2.5 + r1);
    glVertex2i((c2 - c1) / 2 + c1, (r2 - r1) / 2.1 + r1);
    glVertex2i((c2 - c1) / 2.3 + c1, (r2 - r1) / 2.1 + r1);
    glEnd();
}
