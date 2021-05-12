#include <GL/gl.h>
#include <GL/glext.h>
#include "glut.h"
#include <stdio.h>

// Compile Program with this line:
// gcc 2019_q4.c -o 2019_q4 glut32.lib -lopengl32 -lglu32

float p_axis[] = {0, 0.1, 0.2, 0.3, 0.4, 0.5};
float n_axis[] = {0, -0.1, -0.2, -0.3, -0.4, -0.5};

int is_set_array[10][10];

void DrawGridLines()
{
    // Draw 10 x 10 grid i.e. 100 squares
    int i;

    for(i=0; i<11; ++i)
    {
        // Draw Horizontal Lines
        glBegin(GL_LINES);
            glColor3f(0.0,0.0,0.0);
            glVertex2f(-0.5, 0.5 - (i*0.1));
            glVertex2f(0.5, 0.5 - (i*0.1));
        glEnd();

        // Draw Vertical Lines
        glBegin(GL_LINES);
            glColor3f(0.0,0.0,0.0);
            glVertex2f(-0.5 + (i*0.1), 0.5);
            glVertex2f(-0.5 + (i*0.1), -0.5);
        glEnd();
    }
}

void display(void)
{
    //glClear(GL_COLOR_BUFFER_BIT);

    // Make white square
    glBegin(GL_POLYGON);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(-0.5,-0.5);
        glVertex2f(-0.5,0.5);
        glVertex2f(0.5,0.5);
        glVertex2f(0.5,-0.5);
    glEnd();

    DrawGridLines();

    glFlush();

    // Initialise all of set array
    int i;
    int j;

    for(j = 0; j < 10; j++)
    {
        for(i = 0; i < 10; i++)
        {  
            is_set_array[i][j] = 0;
        }
    }

    return;
}

void MyMouse(GLint button, GLint state, GLint x, GLint y)
{
    if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
    {
        // Check if left button pressed in a square
        // x and y are in pixels
        // Grid is 250 x 250 pixels from centre of screen
        if (x > 125 && x < 375 && y > 125 && y < 375)
        {
            // Change colour of square at x, y coordinates in world coordinates
            float w_x = ((x-250.0)/250.0);
            float w_y = (-(y-250.0)/250.0);

            // Need to determine quadrant here
            // TL = 0
            // TR = 1
            // BL = 2
            // BR = 3

            int quadrant = 0;

            if (w_x == 0 && w_y == 0){;}

            else if (w_x >= 0 && w_y >= 0) // For TR
            {
                quadrant = 1;
            }

            else if (w_x <= 0 && w_y <= 0) // For BL
            {
                quadrant = 2;
            }

            else if (w_x >= 0 && w_y <= 0) // For BR
            {
                quadrant = 3;
            }

            // Round down
            /*
            printf("%.4f", w_x);
            printf("\n");
            printf("%.4f", w_y);
            printf("\n");
            */

            // All this for rounding...
            // Convert to int
            int xi = (int) (w_x * 10);
            int yi = (int) (w_y * 10);

            // Convert back to float
            if (xi < 0)
            {
                w_x = n_axis[-xi];
            }

            else
            {
                w_x = p_axis[xi];
            }

            if (yi < 0)
            {
                w_y = n_axis[-yi];
            }

            else
            {
                w_y = p_axis[yi];
            }

            // Different renders based on the quadrant
            // If in TL then coordinates are BR of square
            // If in TR then coordinates are BL of square
            // If in BL then coordinates are TR of square
            // If in BR then coordinates are TL of square
            // So must change coordinates to all be BR of square

            if (quadrant == 1) // For TR
            {
                w_x = w_x + 0.1;
                xi = xi + 1; // For map
            }

            else if (quadrant == 2) // For BL
            {
                w_y = w_y - 0.1;
                yi = yi - 1; // For map
            }

            else if (quadrant == 3) // For BR
            {
                w_x = w_x + 0.1;
                w_y = w_y - 0.1;
                xi = xi + 1; // For map
                yi = yi - 1; // For map
            }

            // Change xi and yi to positive integers for indexing
            if (xi < 0){xi = 10 + xi;}
            if (yi < 0){yi = 10 + yi;}

            glBegin(GL_POLYGON);
            // First check if already set to determine colour
                if (is_set_array[xi][yi] == 1)
                {
                    // Make white
                    glColor3f(1.0,1.0,1.0);
                    is_set_array[xi][yi] = 0;
                }

                else
                {
                    // Make black
                    glColor3f(0.0,0.0,0.0);
                    is_set_array[xi][yi] = 1;
                }

                glVertex2f(w_x - 0.1, w_y); // BL
                glVertex2f(w_x - 0.1, w_y + 0.1); // TL
                glVertex2f(w_x, w_y + 0.1); // TR
                glVertex2f(w_x, w_y); // BR
            glEnd();

            DrawGridLines(); // Redraw gridlines
            glFlush();
        }
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(500,500); // 500 x 500 pixel size
    
    glutCreateWindow("simple");
    glutDisplayFunc(display);

    // Callbacks - functions which respond to events
    glutMouseFunc(MyMouse); // Callback which responds to mouse buttons being clicked

    glutMainLoop();
}
