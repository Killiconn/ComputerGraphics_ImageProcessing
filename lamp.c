#include <GL/gl.h>
#include <GL/glext.h>
#include "glut.h"
#include <math.h>

void makeLampShade(void);
void makeLampBase(void);

void display(void)
{
	glClearColor(0.0,0.0,1.0,1.0);
	// Z-buffer/Depth Buffer test is the most sufisiticated form of hidden surface removal
	// It stops surfaces or objects that are in the background, that are seen when some other object is 
	// in front of them
	// It works by computing the depth of every points in the space.
	// glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH); 	
	// glEnable(GL_DEPTH_TEST);
	// Within the display:
	// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat pos[4] = {0.0,0.0,1.0,0.0};
	glLightfv(GL_LIGHT0,GL_POSITION,pos);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0);

	// makeLampBase();
	makeLampShade();
	
	glFlush();
	return;
}


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

void makeLampBase(void) {
	GLUquadricObj *MySphere;
	MySphere = gluNewQuadric();
	gluQuadricDrawStyle(MySphere, GLU_LINE);
	gluSphere(MySphere,0.5,12,12);
}

void makeLampShade(void) {
	// Changing y to 1 will change the view
    GLfloat x,y=0.0,z,x1,z1,theta=0.0,r=0.6;

	for(int j=0; j<3; j++) // The number of times it goes into the loop the number of spirals you will have
	{	
        y += 0.1; // In increasing this we increase the gaps inbetween each spiral. 
        r -= 0.1;
        glBegin(GL_QUAD_STRIP);
        for(int i=0; i <21; i++)
        {
            theta += 2*M_PI/20;
            x=r*cos(theta); 
			z=r*sin(theta);
            x1=(r-0.1)*cos(theta); 
			z1=(r-0.1)*sin(theta);
            glNormal3f(x/0.1,0,z/0.5);
            glVertex3f(x,y,z);
            glVertex3f(x1,y+0.1,z1);// Increasing y more makes it more like a bucket hat(taller). In other words it makes the dome look more concaved
        }				
        glEnd();
    }
}




int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(500,200);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("lamp");
	glutDisplayFunc(display);
	glutReshapeFunc(MyReshape);

	glEnable(GL_DEPTH_TEST);

	glutMainLoop();
}