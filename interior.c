#include <GL/gl.h>
#include <GL/glext.h>
#include "glut.h"
#include <math.h>

GLfloat xshift = 0.0, zshift = 0.0;

// 20 objects with up to 10 values.
GLfloat objects[5][20]; // Array of created object positions. Need to recreate defined objects everytime redisplay is called

// item tells which type of object it is, e.g. item = 1 is a bed
// nobjects is number of objects created
// Need to press a key to cement the place of an object e.g. q
// k is the index of the current object
// rotation is for rotating objects
GLint k=0, nobjects=0, item=0, rotation = 0; 

GLfloat camx=0.0, camy=1.7, camz=2.0;

GLfloat theta = 0.0; // Angle used to change perspective

GLint birdsEye = 0; // For birds eye view 

void mattress(GLfloat x, GLfloat y, GLfloat z) // x, y, z is the position to create the bed
{
	glPushMatrix();
	glTranslatef(x, y, z); // translate origin to x, y and z
	glScalef(0.6, 0.2, 0.6); // Makes a cuboid; Scales the cube into a cubiod. Numbers represent x, y, and z axes
	glutSolidCube(1.0);
	glPopMatrix();

	return;
}

void bedLeg(GLfloat x, GLfloat y, GLfloat z)
{
	glPushMatrix();
	glTranslatef(x, y, z); // translate origin to x, y and z
	glScalef(0.05, 0.1, 0.05); // Makes a cuboid; Scales the cube into a cubiod. Numbers represent x, y, and z axes
	glutSolidCube(1.0);
	glPopMatrix();

	return;
}

void bed(GLfloat x, GLfloat y, GLfloat z, GLint r)
{
	glPushMatrix(); // Push model view to move bed
	glTranslatef(x, y, z);
	glRotatef(r,0.0,1.0,0.0); // angle, x, y, z : Where x, y and z represent the vector to rotate around
	mattress(0, 0.2, 0); // Made at 0.2 as the mattress is at that height
	// Made at 0.05 as the legs have a height of 0.1, therefore the middle of the legs is at y=0.05
	bedLeg(0.25, 0.05, 0.25); // BR leg
	bedLeg(-0.25, 0.05, 0.25); // BL leg
	bedLeg(0.25, 0.05, -0.25); // TR leg
	bedLeg(-0.25, 0.05, -0.25); // TL leg
	glPopMatrix();

	return;
}

void tabletop(GLfloat x, GLfloat y, GLfloat z)
{
	glPushMatrix();
	glTranslatef(x, y, z); // translate origin to x, y and z
	glScalef(0.3, 0.05, 0.3); 
	glutSolidCube(1.0);
	glPopMatrix();

	return;
}

void tableLeg(GLfloat x, GLfloat y, GLfloat z)
{
	glPushMatrix();
	glTranslatef(x, y, z); // translate origin to x, y and z
	glScalef(0.05, 0.3, 0.05); 
	glutSolidCube(1.0);
	glPopMatrix();

	return;
}

void table(GLfloat x, GLfloat y, GLfloat z, GLint r)
{
	glPushMatrix(); // Push model view to move table
	glTranslatef(x, y, z);
	glRotatef(r,0.0,1.0,0.0);
	tabletop(0, 0.325, 0);
	tableLeg(0.15, 0.15, 0.15); // BR leg
	tableLeg(-0.15, 0.15, 0.15); // BL leg
	tableLeg(0.15, 0.15, -0.15); // TR leg
	tableLeg(-0.15, 0.15, -0.15); // TL leg
	glPopMatrix(); // Pop back model view

	return;
}

void coneShape(GLfloat x, GLfloat y, GLfloat z) {

	glPushMatrix(); // Push model view to move bed
	glTranslatef(x, y, z);

	// Changing y to 1 will change the view
    GLfloat xCS,yCS=0.0,zCS,x1CS,z1CS,thetaCS=0.0,rCS=0.6;

	for(int j=0; j<3; j++) // The number of times it goes into the loop the number of spirals you will have
	{	
        yCS += 0.1; // In increasing this we increase the gaps inbetween each spiral. 
        rCS -= 0.1;
        glBegin(GL_QUAD_STRIP);
        for(int i=0; i <21; i++)
        {
            thetaCS += 2*M_PI/20;
            xCS=rCS*cos(thetaCS); 
			zCS=rCS*sin(thetaCS);
            x1CS=(rCS-0.1)*cos(thetaCS); 
			z1CS=(rCS-0.1)*sin(thetaCS);
            glNormal3f(xCS/0.1,0,zCS/0.5);
            glVertex3f(xCS,yCS,zCS);
            glVertex3f(x1CS,yCS+0.1,z1CS);// Increasing y more makes it more like a bucket hat(taller). In other words it makes the dome look more concaved
        }				
        glEnd();
    }
	glPopMatrix();

	return;
}



void sphere(GLfloat x, GLfloat y, GLfloat z) {
	glPushMatrix(); // Push model view to move bed
	glTranslatef(x, y, z);
	GLUquadricObj *MySphere;
	MySphere = gluNewQuadric();
	// gluQuadricDrawStyle(MySphere, GLU_LINE); // This make it look like a wire sphere. Comment this out for a white circle
	gluSphere(MySphere,0.5,12,12);

	glPopMatrix();

	return;
}

void lamp(GLfloat x, GLfloat y, GLfloat z) {
	glPushMatrix(); // Push model view to move bed
	glTranslatef(x, y, z);
	coneShape(0,0.5,0);
	sphere(0,0.25,0);

	glPopMatrix();

	return;
}

// Function for making a wall --> Glorified cuboid
void wall_1(GLfloat x, GLfloat y, GLfloat z)
{
	glPushMatrix(); // Push model view to move table
	glTranslatef(x, y, z);
	glTranslatef(0.0, 0.25, 0.0);
	//glColor3f(1.0,0.0,0.0);
	glScalef(0.2, 0.5, 1); 
	glutSolidCube(1.0);
	glPopMatrix(); // Pop back model view

	return;
}

// Function for making a wall --> Glorified cuboid
void wall_2(GLfloat x, GLfloat y, GLfloat z)
{	
	// This wall will be perpendicular to the other wall
	glPushMatrix(); // Push model view to move table
	glTranslatef(x, y, z);
	glTranslatef(0.0, 0.25, 0.0);
	//glColor3f(1.0,0.0,0.0);
	glScalef(1, 0.5, 0.2); 
	glutSolidCube(1.0);
	glPopMatrix(); // Pop back model view

	return;
}

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

	// Check for birds eye view
	if(birdsEye == 1)
	{
		gluLookAt(0,camy + 1.0,0,0.0,0.0,0.0,0.0,0.0,-1.0); // Birds eye view
	}

	else
	{
		// y changed to look slightly above floor, angled towards floor
		gluLookAt(camx,camy,camz,0.0,0.0,0.0,0.0,1.0,0.0);
	}

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

    glBegin(GL_POLYGON);  
    // Floor
    glNormal3f(0, 1, 0); // x-z plan, pointing upwards
    glVertex3f(-2, 0, 2); // BL
    glVertex3f(2, 0, 2);    // BR
    glVertex3f(2, 0, -2);   // TR
    glVertex3f(-2, 0, -2);  // TL
    glEnd();
    glPopMatrix();

	// Reset Lighting
	GLfloat ambient_d[4] = {1.0, 1.0, 1.0, 1.0}; // Values correspond to red, blue, green and opacity
	GLfloat diffuse_d[4] = {1.0, 1.0, 1.0, 1.0}; // Values correspond to red, blue, green and opacity
	GLfloat specular_d[4] = {1.0, 1.0, 1.0, 1.0}; // Values correspond to red, blue, green and opacity

	// Apply properties
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_d);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_d);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_d);

    //glTranslatef(xshift,0.0,0.0); // glTranslate changes origin --> Multiplies current matrix by a translation matrix
	//glTranslatef(0.0,zshift,0.0);

    // Remake past beds
	int i;
	for(k=0; k<nobjects; k++)
	{
		if(objects[0][k] == 1) bed(objects[1][k], 0.0, objects[3][k], objects[4][k]);
		else if(objects[0][k] == 2) table(objects[1][k], 0.0, objects[3][k], objects[4][k]);
		else if(objects[0][k] == 3) wall_1(objects[1][k], 0.0, objects[3][k]);
		else if(objects[0][k] == 4) wall_2(objects[1][k], 0.0, objects[3][k]);
		else if(objects[0][k] == 5) coneShape(objects[1][k], 0.0, objects[3][k]);
		else if(objects[0][k] == 6) sphere(objects[1][k], 0.0, objects[3][k]);
		else if(objects[0][k] == 6) lamp(objects[1][k], 0.0, objects[3][k]);
	}
	
	if(item == 1)
		bed(xshift, 0, zshift, rotation); // Current bed
	
	else if(item == 2)
		table(xshift, 0, zshift, rotation);
	
	else if(item == 3)
		wall_1(xshift, 0, zshift);
	
	else if(item == 4)
		wall_2(xshift, 0, zshift);

	else if(item == 5)
		coneShape(xshift, 0, zshift);

	else if(item == 6)
		sphere(xshift, 0, zshift);
	
	else if(item == 7)
		lamp(xshift, 0, zshift);

	glFlush();
	return;
}

// Function for placing objects after they have been created
void MyKeyboard(unsigned char key, GLint x, GLint y)
{
	if(key == 'q') // Cement position of object
	{
		// Save information
		objects[0][k]=item; // item type
		// x, y, z coordinates
		objects[1][k]=xshift;
		objects[2][k]=0.0;
		objects[3][k]=zshift;
		objects[4][k]=rotation;
		nobjects++;

		// Tell display that no object selected now
		item = 0;

		// Reset x and z
		xshift = 0.0;
		zshift = 0.0;

		// Reset rotation
		rotation = 0;

		return;
	}

	// For changing view of scene
	if(key == 'w')
	{
		// Change y to go up
		if(camy < 2.0) camy += 0.1;
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
		camx = 2 * camx;
		camz = 2 * camz;
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

	// Functions for zooming in and out
	if(key == '+')
	{
		if(birdsEye == 0)
		{
			// Only change x and z if in 3D view
			if(camx > 0) camx = camx - 0.1;
			if(camx < 0) camx = camx + 0.1;
			if(camz > 0) camz = camz - 0.1;
			if(camz < 0) camz = camz + 0.1;
		}

		if(camy - 0.1 > 0) camy = camy - 0.1;
	}

	if(key == '-')
	{
		if(birdsEye == 0)
		{
			// Only change x and z if in 3D view
			if(camx > 0) camx = camx + 0.1;
			if(camx < 0) camx = camx - 0.1;
			if(camz > 0) camz = camz + 0.1;
			if(camz < 0) camz = camz - 0.1;
		}

		if(camy + 0.1 < 3.0) camy = camy + 0.1;
	}

	// Have a button to reset view
	if(key == 'r')
	{
		// Reset camx, camy, camz and view
		camx=0.0;
		camy=1.7;
		camz=2.0;
		birdsEye = 0;
	}

	// Need a button for rotating objects
	if(key == 'z')
	{
		rotation += 10;
		if(rotation == 360) rotation = 0;
	}

	glutPostRedisplay(); // Only called if not q

	return;
}

void MySpecial(GLint key, GLint x, GLint y)
 {
    
    if(key == GLUT_KEY_RIGHT) 
    xshift+=0.1; 
    else if(key == GLUT_KEY_LEFT)
    xshift-=0.1;
    else if(key == GLUT_KEY_DOWN)
    zshift-=0.1;
    else if(key == GLUT_KEY_UP)
    zshift+=0.1;
    
    glutPostRedisplay();
}

void mymenu(int value)
{
    // Menu for handling placing objects
    item = value; // Value of current object
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
	
	// Menu for picking objects
    glutCreateMenu(mymenu);
    glutAddMenuEntry("Bed",1);
	glutAddMenuEntry("Table",2);
	glutAddMenuEntry("Wall 1",3);
	glutAddMenuEntry("Wall 2",4);
	glutAddMenuEntry("Cone",5);
	glutAddMenuEntry("Sphere",6);
	glutAddMenuEntry("Lamp",7);
    glutAttachMenu(GLUT_RIGHT_BUTTON); // Shows if you press the right button

	glEnable(GL_DEPTH_TEST);

	glutMainLoop();
}