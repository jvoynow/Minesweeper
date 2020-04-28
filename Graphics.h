#ifndef PS_JV_GRAPHICS_FINAL_GRAPHICS_H
#define PS_JV_GRAPHICS_FINAL_GRAPHICS_H

#include "Game.h"
#include "Button.h"
#include <vector>

#include <cstdlib>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Graphics: public Game {
protected:
    enum Color {
        DARK_GREEN,
        LIGHT_GREEN,
        DARK_BROWN,
        LIGHT_BROWN,
        ONE,
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        WHITE,
        WHITE_HOVER,
        BLACK,
        MENU_BACKGROUND
    };
    constexpr static const struct {
        double r, g, b;
    } colors[] = {
            {155.0/255.0, 200.0/255.0, 65.0/255.0}, // Dark Green
            {171.0/255.0, 214.0/255.0, 81.0/255.0}, // Light Green

            {200.0/255.0, 143.0/255.0, 87.0/255.0}, // Dark Brown
            {213.0/255.0, 169.0/255.0, 125.0/255.0},// Light Brown

            {0, 0, 1}, // One
            {0, 128.0/255.0, 0}, // Two
            {1, 0, 0}, // Three
            {0, 0 , 128.0/255.0}, // Four
            {128.0/255.0, 0, 0}, // Five
            {0, 128.0/255.0, 128.0/255.0}, // Six
            {0,0,0}, // Seven
            {128.0/255.0, 128.0/255.0, 128.0/255.0}, // Eight

            {1.0,1.0,1.0}, // White
            {220.0/255.0, 220.0/255.0, 220.0/255.0}, // White hover
            {0, 0, 0}, // Black
            {92.0/255.0,134.0/255.0,92.0/255.0}, // Menu Background
    };
public:
    // Program initialization NOT OpenGL/GLUT dependent,
// as we haven't created a GLUT window yet
    void init();

// Initialize OpenGL Graphics
    void InitGL();

// Callback functions for GLUT

// Draw the window - this is where all the GL actions are
    void display();

// Trap and process alphanumeric keyboard events
    void kbd(unsigned char key, int x, int y);


// Handle "mouse cursor moved" events
    void cursor(int x, int y);

// Calls itself after a specified time
    void timer(int dummy);

// Handle mouse button pressed and released events
    void mouse(int button, int state, int x, int y);

    void title();

    void create_difficulty_buttons();

    void create_main_menu_button();

    void display_creators();

};

#endif //PS_JV_GRAPHICS_FINAL_GRAPHICS_H