#include <GL/glut.h>
#include <iostream>
#include <math.h> /* sin cos */
using namespace std;


void displayMe(void);
void camp_fire_stick();
void init_camp_fire();
void next_camp_fire();
void animate_fire();

#define SIZE_OF_INIT_FIRE 66 
const int next_fire_co[SIZE_OF_INIT_FIRE][2] =
{
    {195, 11},
    {213, 26},
    {226, 40},
    {240, 57},
    {252, 71},
    {265, 91},
    {277, 105},
    {291, 125},
    {302, 141},
    {309, 154},
    {318, 171},
    {325, 153},
    {329, 131},
    {337, 133},
    {344, 146},
    {350, 161},
    {356, 176},
    {360, 192},
    {365, 211},
    {369, 227},
    {374, 245},
    {378, 263},
    {383, 287},
    {385, 328},
    {383, 343},
    {379, 359},
    {371, 382},
    {357, 401},
    {347, 412},
    {338, 425},
    {323, 436},
    {310, 445},
    {297, 452},
    {282, 458},
    {260, 464},
    {239, 464},
    {223, 464},
    {203, 460},
    {184, 454},
    {163, 445},
    {139, 433},
    {119, 415},
    {102, 389},
    {86, 361},
    {79, 329},
    {77, 301},
    {82, 276},
    {92, 251},
    {101, 229},
    {113, 206},
    {118, 189},
    {123, 167},
    {123, 150},
    {121, 137},
    {115, 122},
    {111, 106},
    {122, 108},
    {121, 109},
    {136, 117},
    {148, 129},
    {159, 137},
    {170, 119},
    {183, 96},
    {193, 77},
    {199, 57},
    {197, 36}
};

const int init_fire_co[SIZE_OF_INIT_FIRE][2] = 
{
    {236, 5},
    {251, 21},
    {263, 40},
    {273, 57},
    {288, 76},
    {299, 95},
    {307, 112},
    {317, 126},
    {326, 142},
    {335, 159},
    {344, 175},
    {353, 192},
    {363, 209},
    {371, 227},
    {378, 243},
    {385, 261},
    {390, 281},
    {394, 297},
    {395, 317},
    {391, 339},
    {387, 356},
    {382, 373},
    {374, 387},
    {365, 400},
    {355, 411},
    {345, 423},
    {333, 432},
    {319, 440},
    {307, 447},
    {291, 455},
    {279, 459},
    {257, 463},
    {239, 464},
    {219, 463},
    {199, 461},
    {179, 455},
    {163, 448},
    {144, 436},
    {130, 423},
    {116, 410},
    {103, 396},
    {95, 380},
    {86, 362},
    {81, 346},
    {78, 330},
    {75, 312},
    {76, 296},
    {80, 278},
    {86, 263},
    {91, 248},
    {99, 232},
    {104, 216},
    {111, 201},
    {119, 188},
    {127, 175},
    {134, 161},
    {143, 147},
    {151, 131},
    {159, 117},
    {168, 102},
    {179, 89},
    {187, 74},
    {197, 60},
    {207, 44},
    {215, 32},
    {222, 20}
};

float t = 0.0;
bool t_inc = true;

void displayMe(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);
    //init_camp_fire();
    //next_camp_fire();
    animate_fire();
    camp_fire_stick();
}

void animate_fire()
{
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(5.0f);
    glBegin(GL_LINE_LOOP);
    //glBegin(GL_POINTS);

    for (int fire_co = 0; fire_co < SIZE_OF_INIT_FIRE; fire_co++)
    {
        glVertex2f( (1.0 - t) * (65 + init_fire_co[fire_co][0]) + t * (65 + next_fire_co[fire_co][0]), (1.0 - t) * (575 - init_fire_co[fire_co][1]) + t * (575 - next_fire_co[fire_co][1]) );
    }
    glEnd();
    glFlush();
}

void init_camp_fire()
{
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(5.0f);
    glBegin(GL_LINE_LOOP);
    //glBegin(GL_POINTS);

    for (int fire_co = 0; fire_co < SIZE_OF_INIT_FIRE; fire_co++)
    {
        glVertex2f( 65 + init_fire_co[fire_co][0], 575 - init_fire_co[fire_co][1]);
    }
    glEnd();
    glFlush();
}

void next_camp_fire()
{
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(5.0f);
    glBegin(GL_LINE_LOOP);
    //glBegin(GL_POINTS);

    for (int fire_co = 0; fire_co < SIZE_OF_INIT_FIRE; fire_co++)
    {
        glVertex2f( 65 + next_fire_co[fire_co][0], 575 - next_fire_co[fire_co][1]);
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
    glVertex2f(100, 125);
    glVertex2f(500, 25);

    // Right to left line
    glVertex2f(100, 25);
    glVertex2f(500, 125);

    glEnd();
    glFlush();
}

void timer(int value)
{
    if ( t_inc )
    {
        t += 0.007;

        if (t >= 1)
        {
            t_inc = false;
        }
    }
    else
    {
        t -= 0.005;

        if (t <= 0)
        {
            t_inc = true;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(3, timer, 1);    
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
    glutTimerFunc(33, timer, 1);

	// Keyborad func
	glutMainLoop();
	return 0;
}
