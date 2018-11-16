#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h> /* sin cos */
#include <iostream>
#define PI 3.14159265

using namespace std;

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void displayMe(void);
void SpecialKeys(int key, int x, int y) {
    if (key == GLUT_KEY_UP)
        xRot -= 5.0f;

    if (key == GLUT_KEY_DOWN)
        xRot += 5.0f;

    if (key == GLUT_KEY_LEFT)
        yRot -= 5.0f;

    if (key == GLUT_KEY_RIGHT)
        yRot += 5.0f;

    xRot = (GLfloat)((const int)xRot % 360);
    yRot = (GLfloat)((const int)yRot % 360);

    // Refresh the Window
    glutPostRedisplay();
}

void displayMe(void) {
    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    glColor3f(1, 1, 1);
    double radius = 2.0;
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i < 360; i++) {
        glVertex3f(radius * cos(i * PI / 180), 2, radius * sin(i * PI / 180));
        glVertex3f(0, -3, 0);
    }
    glEnd();
    radius = 1;
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i < 360; i++) {
        glVertex3f(radius * cos(i * PI / 180), -3, radius * sin(i * PI / 180));
        glVertex3f((radius + 0.1) * cos(i * PI / 180), -3.1, (radius + 0.1) * sin(i * PI / 180));
    }
    glEnd();
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        glVertex3f((radius + 0.1) * cos(i * PI / 180), -3.1, (radius + 0.1) * sin(i * PI / 180));
    }
    glEnd();
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        glVertex3f(radius * cos(i * PI / 180), -3, radius * sin(i * PI / 180));
    }
    glEnd();

    glPopMatrix();
    glFlush();
}

void resize(int w, int h) {
    glViewport(0, 0, w, h);
    GLfloat fAspect = (GLfloat)w / (GLfloat)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // gluPerspective(35.0f, fAspect, 1.0, 40.0);
    glOrtho(-5.0, 5.0, -5.0, 5.0, 5.0, -5.0);
    // glOrtho(-w / 2, w / 2, -h / 2, h / 2, 5.0, -5.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void setup() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(200, 50);
    glutCreateWindow("3d");
    glutReshapeFunc(resize);
    glutDisplayFunc(displayMe);
    glutSpecialFunc(SpecialKeys);
    setup();
    glutMainLoop();
    return 0;
}
