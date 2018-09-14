#include <GL/glut.h>

#include <iostream>

#include <math.h> /* sin cos */

#define PI 3.14159265

int CIRCLE_POINTS = 360;

void displayMe(void)
{
	double radius = 1.0;
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i += 360 / CIRCLE_POINTS)
	{
		glVertex2f(radius * cos(i * PI / 180), radius * sin(i * PI / 180));
	}
	glEnd();
	glFlush();
}

void keyPressed(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '3':
		CIRCLE_POINTS = 3;
		break;
	case '4':
		CIRCLE_POINTS = 4;
		break;
	case '5':
		CIRCLE_POINTS = 5;
		break;
	case '6':
		CIRCLE_POINTS = 6;
		break;
	case '7':
		CIRCLE_POINTS = 7;
		break;
	case '8':
		CIRCLE_POINTS = 8;
		break;
	case '9':
		CIRCLE_POINTS = 9;
		break;

	default:
		CIRCLE_POINTS = 360;
	}

	glutPostRedisplay();
}

void SpecialInput(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		CIRCLE_POINTS++;
		break;
	case GLUT_KEY_DOWN:
		CIRCLE_POINTS--;
		break;
	}

	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Circle");
	glutDisplayFunc(displayMe);

	// Keyborad func
	glutKeyboardFunc(keyPressed);
	glutSpecialFunc(SpecialInput);
	glutMainLoop();
	return 0;
}
