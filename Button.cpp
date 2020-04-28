#include "Button.h"

using namespace std;

Button::Button() {
    current_fill = {1.0,1.0,1.0};
    original_fill = {0,0,0};
    hover_fill = {1.0, 1.0, 1.0};

    x1 = 0;
    x2 = 1;

    y1 = 0;
    y2 = 1;
    text = "";
}

Button::Button(color original, color hover_fill, double x1, double x2, double y1, double y2, string text) {
    current_fill = original;
    original_fill = original;
    this->hover_fill = hover_fill;

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
    return x >= x1 && y >= y1 && x <= x2 && y <= y2;
}

void Button::hover() {
    set_current_fill(hover_fill);
}

void Button::stop_hover() {
    set_current_fill(original_fill);
}


void Button::set_current_fill(color fill) {
    current_fill = fill;
}


void Button::set_original_fill(color fill) {
    original_fill = fill;
}


void Button::set_hover_fill(color fill) {
    hover_fill = fill;
}


void Button::set_x1(double x1) {
    this->x1 = x1;

}

void Button::set_x2(double x2) {
    this->x2 = x2;

}

void Button::set_y1(double y1) {
    this->y1 = y1;

}

void Button::set_y2(double y2) {
    this->y2 = y2;

}

void Button::set_text(std::string text) {
    this->text = std::move(text);
}

std::string Button::get_text() const {
    return text;
}


