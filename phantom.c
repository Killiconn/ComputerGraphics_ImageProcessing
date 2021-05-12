/*

Student 1: William John O'Hanlon - 17477494
Student 2: Killian Connolly - 17303116

*/

#include <GL/gl.h>
#include <GL/glext.h>
#include "glut.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

// gcc phantom.c -o phantom glut32.lib -lopengl32 -lglu32

// For rotate
GLfloat radius=4.0;
GLfloat camx=0.0, camy=0, camz=4.0;
GLfloat theta = 0.0; // Angle used to change perspective

// Checkers for bullets
int left_clicked = 0;

// Big boi bullets stuff
GLfloat bb_x = 4.0;

// Big boi catch stuff
GLfloat catch_x = 0.0;

// Big boi mag stuff
GLfloat mag_y = 0.0;

// Reload
GLint reload_seq = 0;
GLint reload_up = 0;

void gunMain(GLfloat x, GLfloat y, GLfloat z) // x, y, z is the position to create the gun
{
	glPushMatrix();
	glTranslatef(x, y, z); // translate origin to x, y and z
	glScalef(4.0, 1.0, 1.0); // Makes a cuboid; Scales the cube into a cubiod. Numbers represent x, y, and z axes
	glutSolidCube(1.0);
	glPopMatrix();

	return;
}

void gunHandle(GLfloat x, GLfloat y, GLfloat z) // x, y, z is the position to create the gun
{
	glPushMatrix();
	glTranslatef(x - 1.5, y - 1.0, z); // translate origin to x, y and z
	glScalef(1.0, 1.0, 1.0); // Makes a cuboid; Scales the cube into a cubiod. Numbers represent x, y, and z axes
	glutSolidCube(1.0);
	glPopMatrix();

	return;
}

void gunMag(GLfloat x, GLfloat y, GLfloat z) // x, y, z is the position to create the gun
{
	glPushMatrix();
	glTranslatef(x + 0.5, y - 1.0, z); // translate origin to x, y and z
    glTranslatef(0.0, mag_y, 0.0); // translate origin to x, y and z
	glScalef(1, 1, 1); // Makes a cuboid; Scales the cube into a cubiod. Numbers represent x, y, and z axes
	glutSolidCube(1.0);
	glPopMatrix();

	return;
}

void gunCatch(GLfloat x, GLfloat y, GLfloat z) // x, y, z is the position to create the gun
{
	glPushMatrix();
	glTranslatef(x, y, z + 0.6); // translate origin to x, y and z
	glScalef(1.0, 0.2, 0.1); // Makes a cuboid; Scales the cube into a cubiod. Numbers represent x, y, and z axes
	glutSolidCube(1.0);
	glPopMatrix();

	return;
}

void gunStock(GLfloat x, GLfloat y, GLfloat z) // x, y, z is the position to create the gun
{
	glPushMatrix();
	glTranslatef(x - 2.5, y, z); // translate origin to x, y and z
	glScalef(1.0, 1.0, 1.0); // Makes a cuboid; Scales the cube into a cubiod. Numbers represent x, y, and z axes
	glutSolidCube(1.0);
	glPopMatrix();

	return;
}

void gunSilencer(GLfloat x, GLfloat y, GLfloat z) {
	glPushMatrix(); // Push model view to move bed
	glTranslatef(x+2, y, z);
	glRotatef(90, 0.0f, 1.0f, 0.0f);

	GLUquadricObj *MyCylinder;
	MyCylinder = gluNewQuadric();

	glTranslatef(0.0, 0.0, 0.0);
	gluCylinder(MyCylinder,0.5,0.5,2,20,20); // base, top, height ,slices, stacks


	glPopMatrix();

	return;
}

void bullethead(GLfloat x, GLfloat y, GLfloat z){
	glPushMatrix(); // Push model view to move bed
	glTranslatef(x, y, z);
	GLUquadricObj *MySphere;
	MySphere = gluNewQuadric();
	// gluQuadricDrawStyle(MySphere, GLU_LINE); // This make it look like a wire sphere. Comment this out for a white circle
	gluSphere(MySphere,0.3,12,12);

	glPopMatrix();

	return;

}

void bulletshaft(GLfloat x, GLfloat y, GLfloat z) {
	glPushMatrix(); // Push model view to move bed
	glTranslatef(x, y, z);
	glRotatef(90, 0.0f, 1.0f, 0.0f);

	GLUquadricObj *MyCylinder;
	MyCylinder = gluNewQuadric();

	glTranslatef(0.0, 0.0, 0.0);
	gluCylinder(MyCylinder,0.3,0.3,0.4,20,20); // base, top, height ,slices, stacks


	glPopMatrix();

	return;
}

// void bullet(GLfloat x, GLfloat y, GLfloat z) {
// 	glPushMatrix(); // Push model view to move bed
// 	glTranslatef(x, y, z);
	
// 	// bulletshaft(x,y,z);
// 	bullethead(x,y,z);

// 	glPopMatrix();

// 	return;
// }

void phantom(GLfloat x, GLfloat y, GLfloat z) {
	glPushMatrix(); // Push model view to move bed
	glTranslatef(x, y, z);
	
	gunMain(x,y,z);
	gunHandle(x,y,z);
	gunMag(x,y,z);
	gunCatch(catch_x,y,z);
	gunSilencer(x,y,z);
    gunStock(x,y,z);

    if(left_clicked == 1) bullethead(bb_x,y,x);

	glPopMatrix();

	return;
}

void display(void)
{
	glClearColor(0.0,0.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_LIGHTING); // Enable lighting software
	glEnable(GL_LIGHT0); // Enable a particular light source (first light source)

	// glColor is no disabled

	GLfloat pos[4] = {0.0,0.5,1.0,0.0}; // First three variables correspond to x, y and z positions of the light source. Last variable is if light source is at infinity distance away. This makes rays from light source parallel. 
	// 0.0 --> Not infinite, 1.0 --> infinite.
	glLightfv(GL_LIGHT0,GL_POSITION,pos); // Set light source

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    // gluLookAt(0,1.0,0,0.0,0.0,0.0,0.0,0.0,-1.0); // Birds eye view

    // y changed to look slightly above floor, angled towards floor
    gluLookAt(camx,camy,camz,0.0,0.0,0.0,0.0,1.0,0.0);

    glPushMatrix();
	// Going to set lightning for floor here as an example.

	/*
	Diffuse reflection → Rough surface e.g. wood. Light reflected in many directions by object.
	Specular reflection → Shiny or smooth surfaces.
	Ambient reflection → Reflexed off many objects, soup of random light.
	Emissive light → Light emitted from an object.
	*/

    /*
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
    */

    // Make phantom
    phantom(0.0, 0.0, 0.0);

	glFlush();
	return;
}

void MySpecial(GLint key, GLint x, GLint y)
 {  
    if(key == GLUT_KEY_RIGHT)
    {
        theta += 0.1;
		camx = sin(theta);
		camz = cos(theta);
		camx = radius * camx;
		camz = radius * camz;
    }

    else if(key == GLUT_KEY_LEFT)
    {
        theta -= 0.1;
		camx = sin(theta);
		camz = cos(theta);
		camx = radius * camx;
		camz = radius * camz;
    }

    else if(key == GLUT_KEY_DOWN) ;
    else if(key == GLUT_KEY_UP) ;
    
    glutPostRedisplay();
}

// Function for placing objects after they have been created
void MyKeyboard(unsigned char key, GLint x, GLint y)
{
	if(key == 'r')
    {
        reload_seq = 1;
    }


    glutPostRedisplay();
}

void MyMouse(GLint button, GLint state, GLint x, GLint y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
    {
        // Left click pressed
        if(left_clicked == 0) left_clicked = 1;
        else left_clicked = 0;
    }

	return;
}

void MyIdle()
{
	if(left_clicked == 1 && reload_seq != 1) // Shooting
    {
        // Increment catch position
        if(bb_x == 4.0) catch_x = -0.2;
        else if(bb_x >= 5.0) catch_x = 0.0;

        // Increment bullet position
        if(bb_x <= 12.0) bb_x = bb_x + 0.002;
        else bb_x = 4.0;
    }

    if (left_clicked == 0)
    {
        // Reset
        bb_x = 4.0;
    }

	else if(reload_seq == 1)
    {

        if(reload_up == 0)
        {
		    if(mag_y >= -2.0) mag_y = mag_y - 0.0005;
            else reload_up = 1;
        }

        else if(reload_up == 1)
        {
            if(mag_y <= 0.0) mag_y = mag_y + 0.0005;
            else
            {
                // Reset, reload sequence is complete
                mag_y = 0.0;
                reload_up = 0;
                reload_seq = 0;
            }
        }
	}

    glutPostRedisplay();
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
	glutReshapeFunc(MyReshape);
    glutSpecialFunc(MySpecial);
	glutKeyboardFunc(MyKeyboard);
    glutMouseFunc(MyMouse);
	glutIdleFunc(MyIdle);

	glEnable(GL_DEPTH_TEST);

	glutMainLoop();
}