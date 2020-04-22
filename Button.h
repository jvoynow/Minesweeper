#ifndef PS_JV_GRAPHICS_FINAL_BUTTON_H
#define PS_JV_GRAPHICS_FINAL_BUTTON_H

#include <string>

struct color {
    double r, g, b;
};

class Button {
private:
    color current_fill, original_fill, hover_fill;
    double x1, x2, y1, y2;
    std::string text;
public:
    Button();
    Button (color original, color hover_fill, double x1, double x2, double y1, double y2, std::string text);

    std::string get_text() const;

    void set_current_fill(color fill);
    void set_original_fill(color fill);
    void set_hover_fill(color fill);

    void set_x1(double x1);
    void set_x2(double x2);
    void set_y1(double y1);
    void set_y2(double y2);

    void set_text(std::string text);

    void draw(int padding, int length) const;

    bool is_overlapping(int x, int y) const;

    void hover();

    void stop_hover();

};


#endif //PS_JV_GRAPHICS_FINAL_BUTTON_H
