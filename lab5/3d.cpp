#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h> /* sin cos */
#include <iostream>
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
    GLUquadricObj *pObj;  // Quadric Object

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glTranslatef(0.0f, -2.0f, -5.0f);
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    pObj = gluNewQuadric();
    gluQuadricNormals(pObj, GLU_SMOOTH);

    glPushMatrix();

    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluDisk(pObj, 0.0f, 2.0f, 26, 13);

    glColor3f(0.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 2.0f, 2.0f, 5.0f, 26, 13);

    glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();
}

void resize(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-5.0, 5.0, -5.0, 5.0, 5.0, -5.0);
    // glOrtho(0, w, 0, h, 5.0, -5.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void setup() {
    glClearColor(0.25f, 0.25f, 0.50f, 1.0f);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("3d");
    glutReshapeFunc(resize);
    glutDisplayFunc(displayMe);
    glutSpecialFunc(SpecialKeys);
    setup();

    // Keyborad func
    glutMainLoop();
    return 0;
}
