#include <GL/glut.h>
#include <iostream>
#include <math.h> /* sin cos */
using namespace std;


void displayMe(void);
void camp_fire_stick();
void init_camp_fire();

#define SIZE_OF_INIT_FIRE 14 
int init_fire_co[SIZE_OF_INIT_FIRE][2] = 
{
    {300, 500},
    {350, 450},
    {375, 400},
    {395, 338},
    {400, 295},
    {375, 225},
    {325, 200},
    {275, 200},
    {225, 238},
    {210, 270},
    {200, 313},
    {205, 353},
    {225, 400},
    {251, 450},
};

void displayMe(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);
    init_camp_fire();
    camp_fire_stick();
}

void init_camp_fire()
{
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);

    for (int fire_co = 0; fire_co < SIZE_OF_INIT_FIRE; fire_co++)
    {
        glVertex2f(init_fire_co[fire_co][0], init_fire_co[fire_co][1]);
    }
    glEnd();
    glFlush();
        
}

void camp_fire_stick()
{
    glColor3f(0.4f, 0.2f, 0.05f);
    glLineWidth(10.f);
    glBegin(GL_LINES);

    // Left to right line
    glVertex2f(100, 200);
    glVertex2f(500, 100);

    // Right to left line
    glVertex2f(100, 100);
    glVertex2f(500, 200);

    glEnd();
    glFlush();
}

void resize(int w, int h)
{
	glLoadIdentity();
	gluOrtho2D(0, 600, 0, 600);
    glViewport(0, 0 , 600, 600);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Animation");
	glutReshapeFunc(resize);
	glutDisplayFunc(displayMe);

	// Keyborad func
	glutMainLoop();
	return 0;
}
