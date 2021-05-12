#include <GL/gl.h>
#include <GL/glext.h>
#include "glut.h"
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

GLint s = 1;

void drawSolidCircle(GLfloat x, GLfloat y, GLfloat radius)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0);
	glBegin(GL_POLYGON);
    if(s) 
        glColor3f(1.0,0.0,0.0);
    else
        glColor3f(1.0,1.0,0.0);
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

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POLYGON);
		drawSolidCircle(0,0,0.5);
	glEnd();

	glFlush();
	return;
}

void MyMouse(GLint button, GLint state, GLint x, GLint y)
{
    if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
        //Distance formula from x to 250 and y to 250 is less than 0.5
        if (sqrt((x-250)*(x-250) + (y-250)*(y-250)) < 125) {

            if(s) s=0;
            else s=1;
            glutPostRedisplay();
        }
        printf("%f", sqrt((x-250)*(x-250)));
        printf("%s", "\n");
        printf("%f", sqrt((y-250)*(y-250)));
        printf("%s", "\n");
    }
    return;
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(500,500);
    glutInitWindowPosition(500,200);
    glutCreateWindow("mouse");
	glutDisplayFunc(display);
    glutMouseFunc(MyMouse);

	glutMainLoop();
}