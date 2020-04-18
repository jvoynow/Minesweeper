#include "Button.h"

#include <utility>
#include "graphics.h"
using namespace std;

Button::Button(color original, color hover_fill, float x1, float x2, float y1, float y2, string text, float width) {
    current_fill = original;
    original_fill = original;
    this->hover_fill = hover_fill;
    this->width = width;

    this->x1 = x1;
    this->x2 = x2;

    this->y1 = y1;
    this->y2 = y2;

    this->text = std::move(text);
}

void Button::draw(int padding, int length) const{
    glColor3f(current_fill.r, current_fill.g, current_fill.b);
    glBegin(GL_QUADS);
    glVertex2i(x1, y1);
    glVertex2i(x2, y1);
    glVertex2i(x2, y2);
    glVertex2i(x1, y2);
    glEnd();

    glColor3f(colors[BLACK].r, colors[BLACK].g, colors[BLACK].b);
    glRasterPos2i(padding / 2 - length / 2,((y1 + y2) / 2) + 5);
    for (const char &c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

}

bool Button::is_overlapping(int x, int y) const {
    return x >= x1 && x <= x2 && y >= y1 && y <= y2;
}

void Button::hover() {
    set_color(hover_fill);
}

void Button::stop_hover() {
    set_color(original_fill);
}

color Button::get_fill() const {
    return current_fill;
}

void Button::set_color(color fill) {
    this->current_fill = fill;
}

void Button::set_color(float r, float g, float b) {
    current_fill = {r, g, b};
}

