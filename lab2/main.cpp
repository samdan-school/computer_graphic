#include <GL/glut.h>
#include <iostream>

int point_size = 1;
float point_color[3] = {1.0, 1.0, 1.0};

void draw(int x, int y)
{
	glPointSize(point_size);
	glColor3f(point_color[0], point_color[1], point_color[2]);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
	glFlush();
}

void motion(int x, int y)
{
	draw(x, 600 - y);
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		glutMotionFunc(motion);
}

void resize(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);

	gluOrtho2D(0, w, 0, h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'r':
		point_color[0] = 1;
		point_color[1] = 0;
		point_color[2] = 0;
		break;
	case 'b':
		point_color[0] = 0;
		point_color[1] = 0;
		point_color[2] = 1;
		break;
	case 'g':
		point_color[0] = 0;
		point_color[1] = 1;
		point_color[2] = 0;
		break;
	case 'w':
		point_color[0] = 1;
		point_color[1] = 1;
		point_color[2] = 1;
		break;
	case '1':
		point_size = 1;
		break;
	case '2':
		point_size = 2;
		break;
	case '3':
		point_size = 3;
		break;
	case '4':
		point_size = 4;
		break;
	case '5':
		point_size = 5;
		break;
	default:
		break;
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Paint");
	glutReshapeFunc(resize);

	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);

	glutMainLoop();
}
