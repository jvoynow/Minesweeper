#include "Unselected_tile.h"
#include "Graphics.h"

Unselected_tile::Unselected_tile(){
    row = 0;
    column = 0;
    flagged = false;
    adj_bombs = 10;
}

void Unselected_tile::draw() const  {
    // Draw tile at given tile's coordinates
    glColor3f(current_fill.r,current_fill.g,current_fill.b);
    glBegin(GL_QUADS);
    glVertex2i(c1, r1);
    glVertex2i(c2, r1);
    glVertex2i(c2, r2);
    glVertex2i(c1, r2);
    glEnd();
}
