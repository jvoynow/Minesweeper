#include "graphics.h"
#include <iostream>
using namespace std;

GLdouble width, height;
int wd;

void init() {
    width = 1240;
    height = 640;
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(128.0/255.0f, 128.0/255.0f, 128.0/255.0f, 1.0f); // Black and opaque
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // Tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height); // DO NOT CHANGE THIS LINE
    
    // Do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION); // DO NOT CHANGE THIS LINE
    glLoadIdentity(); // DO NOT CHANGE THIS LINE
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f); // DO NOT CHANGE THIS LINE

    // Clear the color buffer with current clearing color
    glClear(GL_COLOR_BUFFER_BIT); // DO NOT CHANGE THIS LINE
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // DO NOT CHANGE THIS LINE

    //main_menu();



    /**
    * This draws an 8x8 board
     * width: 75
     * height: 75
     * padding: 20
    **/
    int tiles_height = 8, tiles_width = 8;
    double x = 0, y = 0, padding = 20;
    double h = (height - 2 * padding)/ tiles_height;
    double w = (width - 2 * padding)/ tiles_width;
    x += padding;
    y += padding;


    for (int row = 0; row < tiles_height; row++) {
        for (int column = 0; column < tiles_width; column++) {
            draw_tile(x, y, w, h, column, row);
            x += w;
        }
        x = padding;
        y += h;
    }

    glFlush();  // Render now
}

void draw_tile(double x, double y, double w, double h, int column, int row) {
    if (row % 2 == 0) {
        ++column;
    }
    if (column % 2 == 1) {
        glColor3f(colors[LIGHT_GREEN].r, colors[LIGHT_GREEN].g,colors[LIGHT_GREEN].b);
    } else {
        glColor3f(colors[DARK_GREEN].r, colors[DARK_GREEN].g,colors[DARK_GREEN].b);
    }
    glBegin(GL_QUADS);
    glVertex2i( x + 0 * w, y + 0 * h);
    glVertex2i(x + 1 * w, y + 0 * h);
    glVertex2i(x + 1 * w, y + 1 * h);
    glVertex2i(x + 0 * w, y + 1 * h);
    glEnd();

    //display_num(58, 58, 7);

}

void main_menu() {
    unsigned char string[] = "Minesweeper";
    int w = glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, string);
    glRasterPos2i(width / 2 - (float)w / 2,60);
    for (char c : string) {
        glColor3f(colors[SEVEN].r, colors[SEVEN].g, colors[SEVEN].b);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }

    unsigned char easy[] = "EASY";
    w = glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, easy);
    menu_colors(w, 1, colors[EASY].r, colors[EASY].g, colors[EASY].b);
    glColor3f(colors[SEVEN].r, colors[SEVEN].g, colors[SEVEN].b);
    glRasterPos2i(width / 2 - (float)w / 2,(height - 60.0) / 4 + 60);
    for (char c : easy) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }


    unsigned char intermediate[] = "INTERMEDIATE";
    w = glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, intermediate);
    menu_colors(w, 2, colors[INTERMEDIATE].r, colors[INTERMEDIATE].g, colors[INTERMEDIATE].b);
    glColor3f(colors[SEVEN].r, colors[SEVEN].g, colors[SEVEN].b);
    glRasterPos2i(width / 2 - (float)w / 2,((height - 60.0) * 2) / 4 + 60);
    for (char c : intermediate) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }


    unsigned char expert[] = "EXPERT";
    w = glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, expert);
    menu_colors(w, 3, colors[EXPERT].r, colors[EXPERT].g, colors[EXPERT].b);
    glColor3f(colors[SEVEN].r, colors[SEVEN].g, colors[SEVEN].b);
    glRasterPos2i(width / 2 - (float)w / 2,((height - 60.0) * 3) / 4 + 60);
    for (char c : expert) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
}

void menu_colors(int w, int num, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2i((width / 2 - (float)w / 2) - 10, ((height - 60.0) * num / 4 + 60) + 18);
    glVertex2i((width / 2 + (float)w / 2) + 10, ((height - 60.0) * num / 4 + 60) + 18);
    glVertex2i((width / 2 + (float)w / 2) + 10, ((height - 60.0) * num / 4 + 60) - 32);
    glVertex2i((width / 2 - (float)w / 2) - 10, ((height - 60.0) * num / 4 + 60) - 32);
    glEnd();
}


void display_num(int x, int y, int num) {
    glColor3f(colors[FIVE].r, colors[FIVE].g, colors[FIVE].b);
    glRasterPos2i(x,y);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '0' + num);
    glEnd();
}


void kbd(unsigned char key, int x, int y)
{
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }
    glutPostRedisplay();
}

void cursor(int x, int y) {
    // if ( x, y inside of game board)
        // if (x, y is open)
            // make background lighter brown
        // else
            // make background lighter green
    // else if (x, y over main menu button)
        // change background color

    glutPostRedisplay();
}

/*void hover() {
    setColor();
}*/

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // if (main_menu(x,y)) -> checks if x, y inside main menu button boundaries
            // init();
        // else if (game is not over && game has not been won)
            // openCell(x,y)

    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        // if (game is not over || game has not been won)
            // toggle_flag(x,y)

    }
    
    glutPostRedisplay();
}

void timer(int dummy) {

    glutPostRedisplay();
    glutTimerFunc(30, timer, dummy);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {

    init();
    
    glutInit(&argc, argv);          // Initialize GLUT
    
    glutInitDisplayMode(GLUT_RGBA);
    
    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(0, 0);
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Minesweeper");

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);
    
    // Our own OpenGL initialization
    initGL();
    
    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);
    
    // handles mouse movement
    glutPassiveMotionFunc(cursor);
    
    // handles mouse click
    glutMouseFunc(mouse);
    
    // handles timer
    glutTimerFunc(0, timer, 0);
    
    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}

