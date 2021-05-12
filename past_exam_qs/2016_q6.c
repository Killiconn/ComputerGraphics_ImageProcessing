#include <GL/gl.h>
#include <GL/glext.h>
#include "glut.h"
#include <math.h>

// 3d box with light source rotating

float theta = M_PI/7;
void display(void)
{
    GLfloat ambient[4] = {0.3, 0.0, 0.0, 1.0};
    GLfloat diffuse[4] = {0.6, 0.0, 0.0, 1.0};
    GLfloat specular[4] = {0.8, 0.6, 0.6, 1.0};
    GLfloat shininess = 32.0;
    GLfloat normal[3] = {0.0,0.0,1.0};
    GLfloat position[4] = {1.0,1.0,1.0,1.0};

    glClearColor(0.0,0.0,1.0,1.0);

    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0);

    position[1]=cos(theta); // Move light in circular motion
    position[2]=sin(theta);

    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    glutSolidCube(0.5);
    glFlush();
    return;
}
void MyReshape(GLsizei w, GLsizei h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // glOrtho(-2.0,2.0,-2.0,2.0,-2.0,2.0);
    glFrustum(-1.0,1.0,-1.0,1.0,0.5,3.0);
    glViewport(0,0,w,h); // We are constantly in the middle of the image
    return;
}
void MyIdle()
{
    theta += 0.001;
    if (theta > 2*M_PI) theta -= 2*M_PI;
        glutPostRedisplay();
    return;
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(500,200);
    glutCreateWindow("cube");
    glutDisplayFunc(display);
    glutReshapeFunc(MyReshape);
    glutIdleFunc(MyIdle);
    glutMainLoop();
}
