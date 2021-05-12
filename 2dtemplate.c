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

/* 
Manual to use program:

- To initiate firework sequence press 'f'.
- To initiate cake movement and separation press 'c'.
- You can rotate the scene by pressing 'd' to go anti-clockwise and 'a' to rotate clockwise.
- Pressing 'r' will reset the animation for infinte birthday surprises.
- Pressing 'p' will switch the view to birds eye view / plan view, and pressing 'p' again will return to 3-D view.
- Pressing 'w' will move the scene view upwards  

*/

// gcc template.c -o template glut32.lib -lopengl32 -lglu32

// For rotate
GLfloat radius=3.0;
GLfloat camx=0.0, camy=1.0, camz=3.0;
GLfloat theta = 0.0; // Angle used to change perspective

// Birds eye view
GLint birdsEye = 0;

// Y changes for rocket
GLfloat rocket_y = 0.0;

// Firework sequence condition
GLint commence_firework_seq = 0;

// Start rockt rising sequence
GLint rocket_rising_seq = 0;

// After firework rises you go into a blast sequence
GLint blast_seq = 0;

//Blasts radius 
GLfloat blast_radius = 0.5;

//Blasts radius 
GLfloat blast_rising_y =3.0;

// Cake moving x, y and z
GLfloat cakex = 0.0;
GLfloat cakez = 0.0;

GLint start_cake_seq = 0;


float theta1 = M_PI/4;
float theta2 = M_PI/4;

void rocketcylinder(GLfloat x, GLfloat y, GLfloat z) // x, y, z is the position to create the gun
{
	glPushMatrix(); // Push model view
	glTranslatef(x, y, z);
	glRotatef(270, 1.0f, 0.0f, 0.0f);

	GLUquadricObj *MyCylinder;
	MyCylinder = gluNewQuadric();

	glTranslatef(0.0, 0.0, 0.0);
	gluCylinder(MyCylinder,0.2,0.2,1,20,20); // base, top, height ,slices, stacks


	glPopMatrix();

	return;
}

void rockethead(GLfloat x, GLfloat y, GLfloat z) // x, y, z is the position to create the gun
{
	glPushMatrix(); // Push model view to move bed
	glTranslatef(x, y+0.5, z);

	glutSolidSphere(0.2,12,12);

	glPopMatrix();

	return;
}

void discoball(GLfloat x, GLfloat y, GLfloat z) {
    glPushMatrix(); // Push model 
	glTranslatef(x, y, z);

    glColor3f(1.0,1.0,1.0); // Set to white
	glutWireSphere(0.2,12,12);

    // Now make coloured points on sphere
    GLfloat dx,dy,r1=0.2,r2=0.5;

	glColor3f(1.0,0.0,0.0);
	dx=r1*cos(theta1);//+r2*cos(theta2);
	dy=r1*sin(theta1);//+r2*sin(theta2);
	
	glPointSize(3.0);
	glBegin(GL_POINTS);
	glVertex2f(x,y);
    

	glPopMatrix();

	return;
}

void firework(GLfloat x, GLfloat y, GLfloat z) {
    glPushMatrix(); // Push model view
	glTranslatef(x, y, z);

    rockethead(x,rocket_y,z);
    rocketcylinder(x,rocket_y,z);

	glPopMatrix();

	return;
}

void blast(GLfloat x, GLfloat y, GLfloat z)
{
    glPushMatrix(); // Push model view
	glTranslatef(x, y, z);

	glTranslatef(x, blast_rising_y, z);
    glColor3ub( rand()%255, rand()%255, rand()%255 ); // random explosion colour
    
	glutSolidSphere(blast_radius,12,12);

    glColor3f(1.0,1.0,1.0);

	glPopMatrix();

	return;
}

void cakeWedge(GLfloat x, GLfloat y, GLfloat z, GLint angle) // x, y, z is the position to create the wedge
{
	glPushMatrix();
	glTranslatef(x, y, z); // translate origin to x, y and z
    
    glRotatef(angle, 0.0, 1.0, 0.0);
    
	// glScalef(4.0, 1.0, 1.0); // Makes a cuboid; Scales the cube into a cubiod. Numbers represent x, y, and z axes
    
    // Top of wedge
    glBegin(GL_POLYGON);
    glColor3f(0.5,0.0,0.1);
    glNormal3f(0, 1, 0); // x-z plan, pointing upwards
    glVertex3f(0, 0, 1.0);
    glVertex3f(0, 0, 0); // Point
    glVertex3f(1.0, 0, 0);
    glEnd();

    // Bottom of wedge
    glBegin(GL_POLYGON);
    glColor3f(0.5,0.0,0.1);  
    glNormal3f(0, 1, 0); // x-z plan, pointing upwards
    glVertex3f(0, 1.0, 1.0);
    glVertex3f(0, 1.0, 0); // Point
    glVertex3f(1.0, 1.0, 0);
    glEnd();

    // Left Side rect
    glBegin(GL_POLYGON);
    glColor3f(0.5,0.0,0.1);
    glNormal3f(0, 1, 0); // x-z plan, pointing upwards
    glVertex3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 1.0, 1.0); // Point
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glEnd();

	// Right Side rect
    glBegin(GL_POLYGON);
    glColor3f(0.5,0.0,0.1);
    glNormal3f(0, 1, 0); // x-z plan, pointing upwards
    glVertex3f(1.0, 0.0, 0.0);
    glVertex3f(1.0, 1.0, 0.0); // Point
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glEnd();

	// Back Side rect
    glBegin(GL_POLYGON);
    glColor3f(0.5,0.0,0.1);
    glNormal3f(0, 1, 0); // x-z plan, pointing upwards
    glVertex3f(1.0, 1.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0); // Point
    glVertex3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 1.0, 1.0);
    glEnd();

    glPopMatrix();

	return;
}

void makeCake(GLfloat x, GLfloat y, GLfloat z)
{
    
    glPushMatrix(); // Push model view to move table
	glTranslatef(x, y, z);

	// Make cake by calling four wedges
    // Wedges thought of as a plane on x-z axis
    cakeWedge(cakex, y, cakez, 0); // Bottom right
    cakeWedge(cakex, y, -cakez, 90); // Top right
    cakeWedge(-cakex, y, -cakez, 180); // Top left
    cakeWedge(-cakex, y, cakez, 270); // Bottom left

	glPopMatrix(); // Pop back model view

	return;
}

void makeScene(GLfloat x, GLfloat y, GLfloat z)
{

    // Render firework and not blast
    if (rocket_rising_seq == 1 && blast_seq == 0)
    {
        firework(0.0,0.0,0.3);
        firework(2.0,0.0,0.-0.3);
        firework(-2.0,0.0,4);
        firework(1.0,0.0,0.0);
        firework(-1.0,0.0,-0.2);
    }

    // Render blast
    else if (rocket_rising_seq == 0 && blast_seq == 1)
    {
        blast(0.0,0.0,0.3);
        blast(2.0,0.0,-0.3);
        blast(-2.0,0.0,4);
        blast(1.0,0.0,0.0);
        blast(-1.0,0.0,-0.2);
    }

    // Rotating ball
    discoball(0, 2.0, 0);
}

void display(void)
{
	glClearColor(0.0,0.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

    // Colour for cake

    // First make cake
    makeCake(0.0, 0.0, 0.0);

    // Floor
    glPushMatrix();
    glBegin(GL_POLYGON); 
    // Colour for floor
    glColor3f(0.0,1.0,1.0);
    glNormal3f(0, 1, 0); // x-z plan, pointing upwards
    glVertex3f(-5, 0, 5); // BL
    glVertex3f(5, 0, 5);    // BR
    glVertex3f(5, 0, -5);   // TR
    glVertex3f(-5, 0, -5);  // TL
    glEnd();
    glPopMatrix();

    // Function which makes the ecard
    glColor3f(1.0,1.0,1.0);
    makeScene(0.0, 0.0, 0.0);

    // if (commence_firework_seq == 1) {
    //     if (rocket_rising_seq == 1 && blast_seq == 0){
    //         firework(0.0,0.0,0.0);
    //     }
    //     else if (rocket_rising_seq == 0 && blast_seq == 1){
    //         blast(0.0,0.0,0.0);
    //     }
    // }

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

    // Rotate scene anti-clockwise
	if(key == 'a')
	{
		// Use trigonometry to get new value of x and z
		theta += 0.1;
		camx = sin(theta);
		camz = cos(theta);
		camx = radius * camx;
		camz = radius * camz;
	}

    // Rotate scene anti-clockwise
	if(key == 'd')
	{
		// Use trigonometry to get new value of x and z
		theta -= 0.1;
		camx = sin(theta);
		camz = cos(theta);
		camx = radius * camx;
		camz = radius * camz;
	}

    // Press p for birds eye view
	if(key == 'p')
	{
		// p for plan
		if(birdsEye == 0) birdsEye = 1;
		else
		{
			birdsEye = 0;
		}
	}

	// Have a button to reset animation all together
	if(key == 'r')
	{
		// Reset camx, camy, camz and view
		camx=0.0;
		camy=1.0;
		camz=radius;
		birdsEye = 0;

        // Y changes for rocket
        rocket_y = 0.0;

        // Firework sequence condition
        commence_firework_seq = 0;

        // Start rockt rising sequence
        rocket_rising_seq = 0;

        // After firework rises you go into a blast sequence
        blast_seq = 0;

        //Blasts radius 
        blast_radius = 0.5;

        //Blasts radius 
        blast_rising_y = 3.0;

        // Cake moving x, y and z
        cakex = 0.0;
        cakez = 0.0;

        start_cake_seq = 0;
	}

    if(key == 'f')
    {
        commence_firework_seq = 1;
        rocket_rising_seq = 1;
    }

    if(key == 'c') // Move cake pieces out
    {
        // Start to increment cake position in idle function
        if(start_cake_seq == 0) start_cake_seq = 1;
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
    if (commence_firework_seq == 1) {
        if (rocket_rising_seq == 1) {
            if (rocket_y <= 3) {
                rocket_y += 0.005;
            }
            else {
                // start different sequence of display
                // Need to get rid of firework rocket
                // Then have spheres that gradually descrease in raduis
                // Then reset rocket_y
                // blast_seq
                blast_seq = 1;
                rocket_rising_seq = 0;
                rocket_y = 0;
                
            }
        }
        else if(blast_seq == 1) {
            if (blast_radius > 0) {
                blast_radius -= 0.001;
                blast_rising_y += 0.005;
            }
            else {
                blast_rising_y = 3;
                blast_seq = 0;
                rocket_rising_seq = 1;
                blast_radius = 0.5;
            }
        }
    }
    
    if(start_cake_seq == 1)
    {
        if(cakex < 1.0)
        {
            cakex += 0.001;
            cakez += 0.001;
        }

        else
        {
            start_cake_seq = 0;
        }
    }
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
	
	glEnable(GL_DEPTH_TEST);

	glutMainLoop();
}