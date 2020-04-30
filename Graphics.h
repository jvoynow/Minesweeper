#ifndef PS_JV_GRAPHICS_FINAL_GRAPHICS_H
#define PS_JV_GRAPHICS_FINAL_GRAPHICS_H

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

#include "Unselected_flag.h"
#include "Selected_safe.h"
#include "Selected_bomb.h"
#include "Tile.h"
#include "Unselected_tile.h"
#include "Button.h"


#include <iostream>
#include <ctime>
#include <vector>


// Program initialization NOT OpenGL/GLUT dependent,
// as we haven't created a GLUT window yet
    void init();

// Initialize OpenGL Graphics
    void initGL();

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

    void display_loss();

    void display_win();

enum Color {
    DARK_GREEN,
    LIGHT_GREEN,
    GREEN_HOVER,
    DARK_BROWN,
    LIGHT_BROWN,
    BROWN_HOVER,
    WHITE,
    WHITE_HOVER,
    BLACK,
    MENU_BACKGROUND
};
    static const struct {
        double r, g, b;
    } colors[] = {
            {155.0/255.0, 200.0/255.0, 65.0/255.0}, // Dark Green
            {171.0/255.0, 214.0/255.0, 81.0/255.0}, // Light Green
            {200.0/255.0, 235.0/255.0, 120.0/255.0}, // Green Hover

            {200.0/255.0, 143.0/255.0, 87.0/255.0}, // Dark Brown
            {213.0/255.0, 169.0/255.0, 125.0/255.0},// Light Brown
            {226.0/255.0, 193.0/255.0, 170.0/255.0}, // Brown Hover

            {1.0,1.0,1.0}, // White
            {220.0/255.0, 220.0/255.0, 220.0/255.0}, // White hover
            {0, 0, 0}, // Black
            {100.0/255.0, 150.0/255.0, 100.0/255.0}, // Menu Background
    };

#endif //PS_JV_GRAPHICS_FINAL_GRAPHICS_H
