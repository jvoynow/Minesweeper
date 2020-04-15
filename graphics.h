#ifndef graphics_h
#define graphics_h

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

//#define

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

// Trap and process special keyboard events
void kbdS(int key, int x, int y);

// Handle "mouse cursor moved" events
void cursor(int x, int y);

// Calls itself after a specified time
void timer(int dummy);

// Handle mouse button pressed and released events
void mouse(int button, int state, int x, int y);


class Graphics {
public:

private:
    enum Colors {
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
        EIGHT
    };
    constexpr static const struct {
        float r, g, b;
    } colors[] = {
            {161.0/255.0, 207.0/255.0, 72.0/255.0}, // Dark Green
            {171.0/255.0, 214.0/255.0, 81.0/255.0}, // Light Green

            {213.0/255.0, 182.0/255.0, 153.0/255.0}, // Dark Brown
            {227.0/255.0, 293.0/255.0, 156.0/255.0}, // Light Brown

            {0, 0, 1}, // One
            {0, 128.0/255.0, 0}, // Two
            {1, 0, 0}, // Three
            {0, 0 , 128.0/255.0}, // Four
            {128.0/255.0, 0, 0}, // Five
            {0, 128.0/255.0, 128.0/255.0}, // Six
            {0,0,0}, // Seven
            {128.0/255.0, 128.0/255.0, 128.0/255.0}, // Eight
    };
};


#endif /* graphics_h */
