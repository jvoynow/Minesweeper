#ifndef PS_JV_GRAPHICS_FINAL_BUTTON_H
#define PS_JV_GRAPHICS_FINAL_BUTTON_H

#include <string>

struct color {
    float r, g, b;
};

class Button {
private:
    color current_fill{}, original_fill{}, hover_fill{};
    float x1, x2, y1, y2, width;
    std::string text;
public:
    Button (color original, color hover_fill, float x1, float x2, float y1, float y2, std::string text, float width);

    color get_fill() const;

    void set_color(color fill);
    void set_color(float r, float g, float b);

    void draw(int padding, int length) const;

    bool is_overlapping(int x, int y) const;

    void hover();

    void stop_hover();

};


#endif //PS_JV_GRAPHICS_FINAL_BUTTON_H
