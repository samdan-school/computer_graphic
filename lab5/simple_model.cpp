#include <GL/glut.h>
#include <GL/glu.h>
#include <iostream>

using namespace std;

void display()
{
	GLUquadricObj *pObj;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	glTranslatef(0.0f, -1.0f, -4.0f);
	// glRotatef(0, 1.0f, 0.0f, 0.0f);
	// glRotatef(0, 0.0f, 1.0f, 0.0f);
	GLfloat rot = (GLfloat)(45 % 360);
	// glRotatef(rot, 0.0f, 0.0f, 1.0f);

	pObj = gluNewQuadric();

	gluQuadricDrawStyle(pObj, GLU_FILL);
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glColor3f(0.5f, 0.35f, 0.05f);

	glPopMatrix();

	glPointSize(1.0f);
	glBegin(GL_POLYGON);
	glVertex3f(2, 2, -2);
	glVertex3f(2, 3, -2);
	glVertex3f(2, 2, 3);
	glVertex3f(2, 3, 3);
	glEnd();

	glutSwapBuffers();
	gluDeleteQuadric(pObj);
}

void resize(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-4, 4, -4, 4, 4, -4);
	glViewport(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("SIMPLE MODEL");
	glutReshapeFunc(resize);
	glutDisplayFunc(display);

	glutMainLoop();
	return 0;
}