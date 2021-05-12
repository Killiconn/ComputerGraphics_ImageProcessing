#include <GL/gl.h>
#include <GL/glext.h>
#include "glut.h"
#include <stdio.h>
#include <stdbool.h>

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1.0,1.0); 
	glBegin(GL_POLYGON);
		glVertex2f(-0.5,-0.5);
		glVertex2f(-0.5,0.5);
		glVertex2f(0.5,0.5);
		glVertex2f(0.5,-0.5);
	glEnd();

	glFlush();
	return;
}


void MyMouse(GLint button, GLint state, GLint x, GLint y)
{
    static int first=1;
    if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
    {
        float w_x = ((x-250.0)/250.0);
        float w_y = (-(y-250.0)/250.0);

        // Not using world coordinated
        if(x > 120 && x < 130 && y > 120 && x < 130){
            glColor3f(0.0,0.0,0.0);
            glBegin(GL_POLYGON);
                glVertex2f(-0.5+w_x,0.45+w_y);
                glVertex2f(-0.5+w_x,0.5+w_y); //
                glVertex2f(-0.45+w_x,0.5+w_y);
                glVertex2f(-0.45+w_x,0.45+w_y);
            glEnd(); 
            glFlush();
        }

        

        printf("%f", w_x);
        printf("%s", "\n");
        printf("%f", w_y);
        printf("%s", "\n");
        printf("%s", "\n");

        printf("%d", x);
        printf("%s", "\n");
        printf("%d", y);
        printf("%s", "\n");
        printf("%s", "\n");

    }
    else {
        glutPostRedisplay();
    }
   
    return;
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(500,200);
    glutCreateWindow("simple");
	glutDisplayFunc(display);
    glutMouseFunc(MyMouse); //If you hold down a click with passive you wont update the variables
	glutMainLoop();
}