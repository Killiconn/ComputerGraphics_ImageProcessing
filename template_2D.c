
/*

Student 1: William John O'Hanlon - 17477494
Student 2: Killian Connolly - 17303116

*/

#include <GL/gl.h>
#include <GL/glext.h>
#include "glut.h"
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

GLfloat theta = 0.0;

void drawSolidCircle(GLfloat x, GLfloat y, GLfloat radius)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0);
	glBegin(GL_POLYGON);
    GLfloat theta = 0.0;
	for (int i = 0; i <= 300; i++) // i has to be larger or equal to the number of sides
    {
    	theta = 2 * M_PI * i / 300; // Divide by the number of sides
    	x = cos(theta) * radius;
        y = sin(theta) * radius;
        glVertex2d(x, y);
    }
    glEnd();
    glPopMatrix();
}

void drawHollowCircle(GLfloat radius)
{
    GLfloat x=0,y=0;
	
    for (int i = 0; i < 1000 ; i ++) {
        theta += 0.01;

        x=radius*cos(theta);
	    y=radius*sin(theta);
        glBegin(GL_POINTS);
	    glVertex2f(x,y);
	    glEnd();
    }
    glFlush();
	glutPostRedisplay();

	return;
}

void square()
{
    glBegin(GL_POLYGON);
    glColor3f(1.0,1.0,1.0);
    glVertex2f(-0.5,-0.5);
    glVertex2f(-0.5,0.5);
    glVertex2f(0.5,0.5);
    glVertex2f(0.5,-0.5);
    glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawSolidCircle(0.0, 0.0, 1.0);

    glFlush();
}

void MyMouse(GLint button, GLint state, GLint x, GLint y)
{
    if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
    {}
}

void mymenu(int value) {};

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(500,500); // 500 x 500 pixel size
    
    glutCreateWindow("simple");
    glutDisplayFunc(display);

    // Callbacks - functions which respond to events
    glutMouseFunc(MyMouse); // Callback which responds to mouse buttons being clicked

    // Menu 
    GLint id;
    id = glutCreateMenu(mymenu);
    glutAddMenuEntry("Blue",1);
    glutAttachMenu(GLUT_RIGHT_BUTTON); // Shows if you press the right button

    glutMainLoop();
}