#include "graphics.h"
#include "Game.h"
#include <iostream>
#include <vector>

using namespace std;

GLdouble width, height, padding;
int tiles_width = 0, tiles_height = 0;
int wd;
Button easy, intermediate, expert, main_menu;
Game game;


void init() {
    width = 1240;
    height = 640;
    padding = 300;
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(colors[MENU_BACKGROUND].r, colors[MENU_BACKGROUND].g, colors[MENU_BACKGROUND].b, 1.0f);
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


    title();

    if (tiles_width == 0 && tiles_height == 0) {
        create_difficulty_buttons();
    } else if (tiles_width != 0 && tiles_height != 0){
        create_main_menu_button();
    }

    double x = padding, y = 0;
    double h = (height)/ tiles_height;
    double w = (width - padding)/ tiles_width;


    for (int row = 0; row < tiles_height; row++) {
        for (int column = 0; column < tiles_width; column++) {
            draw_tile(x, y, w, h, column, row);
            x += w;
        }
        x = padding;
        y += h;
    }

    display_creators();

    glFlush();  // Render now
}

void create_main_menu_button() {
    unsigned char menu[] = "MAIN MENU";
    if (main_menu.get_text() != "MAIN MENU") {
        main_menu.set_current_fill({colors[WHITE].r, colors[WHITE].g, colors[WHITE].b});
        main_menu.set_original_fill({colors[WHITE].r, colors[WHITE].g, colors[WHITE].b});
        main_menu.set_hover_fill({colors[WHITE_HOVER].r, colors[WHITE_HOVER].g, colors[WHITE_HOVER].b});
        main_menu.set_x1((((double)padding / 2 - ((double)(glutBitmapLength(GLUT_BITMAP_HELVETICA_18, menu)) / 2)) - 30));
        main_menu.set_x2((((double)padding / 2 + ((double)(glutBitmapLength(GLUT_BITMAP_HELVETICA_18, menu)) / 2)) + 30));
        main_menu.set_y1(((double)height - 100));
        main_menu.set_y2(((double)height - 64));
        main_menu.set_text("MAIN MENU");
    }
    main_menu.draw(padding, glutBitmapLength(GLUT_BITMAP_HELVETICA_18, menu));
}

void create_difficulty_buttons() {
    unsigned char easy_chars[] = "EASY";
    unsigned char intermediate_chars [] = "INTERMEDIATE";
    unsigned char expert_chars[] = "EXPERT";
    if (easy.get_text() != "EASY") {
        easy.set_current_fill({colors[WHITE].r, colors[WHITE].g, colors[WHITE].b});
        easy.set_original_fill({colors[WHITE].r, colors[WHITE].g, colors[WHITE].b});
        easy.set_hover_fill({colors[WHITE_HOVER].r, colors[WHITE_HOVER].g, colors[WHITE_HOVER].b});
        easy.set_x1((((double)padding / 2 - ((double)(glutBitmapLength(GLUT_BITMAP_HELVETICA_18, intermediate_chars)) / 2)) - 10));
        easy.set_x2((((double)padding / 2 + ((double)(glutBitmapLength(GLUT_BITMAP_HELVETICA_18, intermediate_chars)) / 2)) + 10));
        easy.set_y1((((double)height / 2) - 106));
        easy.set_y2((((double)height / 2) - 70));
        easy.set_text("EASY");
    }
    if (intermediate.get_text() != "INTERMEDIATE") {
        intermediate.set_current_fill({colors[WHITE].r, colors[WHITE].g, colors[WHITE].b});
        intermediate.set_original_fill({colors[WHITE].r, colors[WHITE].g, colors[WHITE].b});
        intermediate.set_hover_fill({colors[WHITE_HOVER].r, colors[WHITE_HOVER].g, colors[WHITE_HOVER].b});
        intermediate.set_x1((((double)padding / 2 - ((double)(glutBitmapLength(GLUT_BITMAP_HELVETICA_18, intermediate_chars)) / 2)) - 10));
        intermediate.set_x2((((double)padding / 2 + ((double)(glutBitmapLength(GLUT_BITMAP_HELVETICA_18, intermediate_chars)) / 2)) + 10));
        intermediate.set_y1((((double)height / 2) - 66));
        intermediate.set_y2((((double)height / 2) - 26));
        intermediate.set_text("INTERMEDIATE");
    }

    if (expert.get_text() != "EXPERT"){
        expert.set_current_fill({colors[WHITE].r, colors[WHITE].g, colors[WHITE].b});
        expert.set_original_fill({colors[WHITE].r, colors[WHITE].g, colors[WHITE].b});
        expert.set_hover_fill({colors[WHITE_HOVER].r, colors[WHITE_HOVER].g, colors[WHITE_HOVER].b});
        expert.set_x1((((double)padding / 2 - ((double)(glutBitmapLength(GLUT_BITMAP_HELVETICA_18, intermediate_chars)) / 2)) - 10));
        expert.set_x2((((double)padding / 2 + ((double)(glutBitmapLength(GLUT_BITMAP_HELVETICA_18, intermediate_chars)) / 2)) + 10));
        expert.set_y1((((double)height / 2) - 22));
        expert.set_y2((((double)height / 2) +14));
        expert.set_text("EXPERT");
    }

    easy.draw(padding, glutBitmapLength(GLUT_BITMAP_HELVETICA_18, easy_chars));
    intermediate.draw(padding, glutBitmapLength(GLUT_BITMAP_HELVETICA_18, intermediate_chars));
    expert.draw(padding, glutBitmapLength(GLUT_BITMAP_HELVETICA_18, expert_chars));
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

    display_num(x + 0.5 * w, y + 0.5 * h ,7);

}

void title() {
    unsigned char title[] = "Minesweeper";
    int w = glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, title);
    glRasterPos2i((double)padding / 2 - (double)w / 2,60);
    glColor3f(colors[BLACK].r, colors[BLACK].g, colors[BLACK].b);
    for (char c : title) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
}


void display_num(double x, double y, int num) {
    glColor3f(colors[FIVE].r, colors[FIVE].g, colors[FIVE].b);
    glRasterPos2i(x,y);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '0' + num);
    glEnd();
}

void display_creators() {
    unsigned char opening[] = "Created by:", parker[] = "Parker Strawbridge", sep[] = "&", jamie[] = "Jamie Voynow";
    int w = glutBitmapLength(GLUT_BITMAP_HELVETICA_10, opening);
    glColor3f(colors[BLACK].r, colors[BLACK].g, colors[BLACK].b);
    glRasterPos2i(double(padding) / 5 - (double)w / 2,height - 22);
    for (char c : opening) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    w = glutBitmapLength(GLUT_BITMAP_HELVETICA_10, parker);
    glRasterPos2i(double(padding) / 2 - (double)w / 2,height - 36);
    for (char c : parker) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    w = glutBitmapLength(GLUT_BITMAP_HELVETICA_10, sep);
    glRasterPos2i(double(padding) / 2 - (double)w / 2,height - 22);
    for (char c : sep) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    w = glutBitmapLength(GLUT_BITMAP_HELVETICA_10, jamie);
    glRasterPos2i(double(padding) / 2 - (double)w / 2,height - 8);
    for (char c : jamie) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
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
    if (easy.is_overlapping(x,y)) {
        easy.hover();
    } else {
        easy.stop_hover();
    }
    if (intermediate.is_overlapping(x,y)) {
        intermediate.hover();
    } else {
        intermediate.stop_hover();
    }
    if (expert.is_overlapping(x,y)) {
        expert.hover();
    } else {
        expert.stop_hover();
    }
    if (main_menu.is_overlapping(x,y)) {
        main_menu.hover();
    } else {
        main_menu.stop_hover();
    }

    glutPostRedisplay();
}


// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (easy.is_overlapping(x,y) && game.get_tile_width() == 0 && game.get_tile_height() == 0) {
            tiles_height = 8;
            tiles_width = 8;

            game.set_tile_width(8);
            game.set_tile_height(8);
            game.set_bomb_count(10);
        } else if (intermediate.is_overlapping(x,y) && game.get_tile_width() == 0 && game.get_tile_height() == 0) {
            tiles_height = 16;
            tiles_width = 16;

            game.set_tile_width(16);
            game.set_tile_height(16);
            game.set_bomb_count(40);
        } else if (expert.is_overlapping(x,y) && game.get_tile_width() == 0 && game.get_tile_height() == 0) {
            tiles_height = 16;
            tiles_width = 30;

            game.set_tile_width(30);
            game.set_tile_height(16);
            game.set_bomb_count(99);
        } else if (main_menu.is_overlapping(x, y) && game.get_tile_width() != 0 && game.get_tile_height() != 0) {
            tiles_height = 0;
            tiles_width = 0;

            game.set_tile_height(0);
            game.set_tile_width(0);
            game.set_bomb_count(0);
        }
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

    glutInit(&argc, argv);          // Initialize GLUT
    init();

    
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

