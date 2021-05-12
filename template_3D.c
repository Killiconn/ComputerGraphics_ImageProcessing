/*

Student 1: William John O'Hanlon - 17477494
Student 2: Killian Connolly - 17303116

*/

#include <GL/gl.h>
#include <GL/glext.h>
#include "glut.h"
#include <math.h>
#include <stdbool.h>

// gcc template.c -o template glut32.lib -lopengl32 -lglu32

// For rotate
GLfloat radius=2.0;
GLfloat camx=0.0, camy=0.5, camz=2.0;
GLfloat theta = 0.0; // Angle used to change perspective

// Birds eye view
GLint birdsEye = 0;

void display(void)
{
	glClearColor(0.0,0.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_LIGHTING); // Enable lighting software
	glEnable(GL_LIGHT0); // Enable a particular light source (first light source)

	// glColor is no disabled

	GLfloat pos[4] = {0.0,1.0,1.0,0.0}; // First three variables correspond to x, y and z positions of the light source. Last variable is if light source is at infinity distance away. This makes rays from light source parallel. 
	// 0.0 --> Not infinite, 1.0 --> infinite.
	glLightfv(GL_LIGHT0,GL_POSITION,pos); // Set light source

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(birdsEye == 1) gluLookAt(0,radius,0,0.0,0.0,0.0,0.0,0.0,-1.0); // Birds eye view

    // y changed to look slightly above floor, angled towards floor
    else gluLookAt(camx,camy,camz,0.0,0.0,0.0,0.0,1.0,0.0);

    glPushMatrix();
	// Going to set lightning for floor here as an example.

	/*
	Diffuse reflection → Rough surface e.g. wood. Light reflected in many directions by object.
	Specular reflection → Shiny or smooth surfaces.
	Ambient reflection → Reflexed off many objects, soup of random light.
	Emissive light → Light emitted from an object.
	*/

	GLfloat ambient[4] = {0.3, 0.0, 0.0, 1.0}; // Values correspond to red, blue, green and opacity
	GLfloat diffuse[4] = {0.6, 0.0, 0.0, 1.0}; // Values correspond to red, blue, green and opacity
	GLfloat specular[4] = {0.8, 0.6, 0.6, 1.0}; // Values correspond to red, blue, green and opacity
	GLfloat shininess = 32.0; // Determines size of specularity i.e. bright spot from a direct light source.

	// Apply properties
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

	// Reset Lighting
	GLfloat ambient_d[4] = {1.0, 1.0, 1.0, 1.0}; // Values correspond to red, blue, green and opacity
	GLfloat diffuse_d[4] = {1.0, 1.0, 1.0, 1.0}; // Values correspond to red, blue, green and opacity
	GLfloat specular_d[4] = {1.0, 1.0, 1.0, 1.0}; // Values correspond to red, blue, green and opacity

	// Apply default properties
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_d);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_d);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_d);

	// Top of wedge
    glBegin(GL_POLYGON);  
    glNormal3f(0, 1, 0); // x-z plan, pointing upwards
    glVertex3f(0, 0, 1.0);
    glVertex3f(0, 0, 0); // Point
    glVertex3f(1.0, 0, 0);
    glEnd();

    // Bottom of wedge
    glBegin(GL_POLYGON);  
    glNormal3f(0, 1, 0); // x-z plan, pointing upwards
    glVertex3f(0, 1.0, 1.0);
    glVertex3f(0, 1.0, 0); // Point
    glVertex3f(1.0, 1.0, 0);
    glEnd();

    // Left Side rect
    glBegin(GL_POLYGON);  
    glNormal3f(0, 1, 0); // x-z plan, pointing upwards
    glVertex3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 1.0, 1.0); // Point
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glEnd();

	// Right Side rect
    glBegin(GL_POLYGON);  
    glNormal3f(0, 1, 0); // x-z plan, pointing upwards
    glVertex3f(1.0, 0.0, 0.0);
    glVertex3f(1.0, 1.0, 0.0); // Point
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glEnd();

	// Back Side rect
    glBegin(GL_POLYGON);  
    glNormal3f(0, 1, 0); // x-z plan, pointing upwards
    glVertex3f(1.0, 1.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0); // Point
    glVertex3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 1.0, 1.0);
    glEnd();

	glFlush();
	return;
}

void MySpecial(GLint key, GLint x, GLint y)
 {
    
    if(key == GLUT_KEY_RIGHT) ; 
    else if(key == GLUT_KEY_LEFT) ;
    else if(key == GLUT_KEY_DOWN) ;
    else if(key == GLUT_KEY_UP) ;
    
    glutPostRedisplay();
}

// Function for placing objects after they have been created
void MyKeyboard(unsigned char key, GLint x, GLint y)
{
	// For changing view of scene
	if(key == 'w')
	{
		// Change y to go up
		if(camy < 3.0) camy += 0.1;
	}

	if(key == 's')
	{
		// Change y to go down
		if(camy > 0.1) camy -= 0.1;
	}

	if(key == 'a')
	{
		// Use trigonometry to get new value of x and z
		theta += 0.1;
		camx = sin(theta);
		camz = cos(theta);
		camx = 2 * camx;
		camz = 2 * camz;
	}

	if(key == 'd')
	{
		// Use trigonometry to get new value of x and z
		theta -= 0.1;
		camx = sin(theta);
		camz = cos(theta);
		camx = radius * camx;
		camz = radius * camz;
	}

	if(key == 'p')
	{
		// p for plan
		if(birdsEye == 0) birdsEye = 1;
		else
		{
			birdsEye = 0;
			key = 'r'; // runs reset code below
		}
	}

		// Have a button to reset view
	if(key == 'r')
	{
		// Reset camx, camy, camz and view
		camx=0.0;
		camy=0.5;
		camz=radius;
		birdsEye = 0;
	}

    glutPostRedisplay();
}

void mymenu(int value)
{
    // Menu
	// if(value == 1) ;
	glutPostRedisplay();
}

void MyIdle()
{
	glutPostRedisplay();
	return;
}

// For window reshape and 3-D
void MyReshape(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
//	glOrtho(-2.0,2.0,-2.0,2.0,0.3,5.0);
	glFrustum(-1.0,1.0,-1.0,1.0,0.3,5.0);
//	gluPerspective(60,1.0,0.3,5.0);
	glViewport(0,0,w,h);
	return;
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(500,200);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("cube");
	glutDisplayFunc(display);

	// Callbacks
	glutReshapeFunc(MyReshape);
    glutSpecialFunc(MySpecial);
	glutKeyboardFunc(MyKeyboard);
	glutIdleFunc(MyIdle);
	
	// Menu for picking objects
    glutCreateMenu(mymenu);
    glutAddMenuEntry("eXAMPLE",1);
	
    glutAttachMenu(GLUT_RIGHT_BUTTON); // Shows if you press the right button

	glEnable(GL_DEPTH_TEST);

	glutMainLoop();
}