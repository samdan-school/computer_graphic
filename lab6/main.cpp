#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h> /* sin cos */
#include <iostream>
#include <vector>
#define PI 3.14159265

using namespace std;

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void displayMe(void);
void SpecialKeys(int key, int x, int y) {
    if (key == GLUT_KEY_UP) xRot -= 5.0f;

    if (key == GLUT_KEY_DOWN) xRot += 5.0f;

    if (key == GLUT_KEY_LEFT) yRot -= 5.0f;

    if (key == GLUT_KEY_RIGHT) yRot += 5.0f;

    xRot = (GLfloat)((const int)xRot % 360);
    yRot = (GLfloat)((const int)yRot % 360);

    // Refresh the Window
    glutPostRedisplay();
}

void ReduceToUnit(float *vector) {
    float length;
    length = (float)sqrt((vector[0] * vector[0]) + (vector[1] * vector[1]) +
                         (vector[2] * vector[2]));
    if (length == 0.0f) length = 1.0f;
    vector[0] /= length;
    vector[1] /= length;
    vector[2] /= length;
}
void calcNormal(vector<float> radius, vector<float> y, int i, int j, float *out) {
    float v1[3], v2[3];

    // v1[x] = v[0][x] - v[1][x];
    // v1[y] = v[0][y] - v[1][y];
    // v1[z] = v[0][z] - v[1][z];
    v1[0] = radius[j] * cos(i * PI / 180) - radius[j + 1] * cos(i * PI / 180);
    v1[1] = y[j] - y[j + 1];
    v1[2] = radius[j] * sin(i * PI / 180) - radius[j + 1] * sin(i * PI / 180);

    // v2[x] = v[1][x] - v[2][x];
    // v2[y] = v[1][y] - v[2][y];
    // v2[z] = v[1][z] - v[2][z];
    v1[0] = radius[j] * cos(i * PI / 180) - radius[j] * cos(i + 1 * PI / 180);
    v1[1] = y[j] - y[j];
    v1[2] = radius[j] * sin(i * PI / 180) - radius[j] * sin(i + 1 * PI / 180);

    out[0] = v1[1] * v2[2] - v1[2] * v2[1];
    out[1] = v1[2] * v2[0] - v1[0] * v2[2];
    out[2] = v1[0] * v2[1] - v1[1] * v2[0];

    ReduceToUnit(out);
}

void displayMe(void) {
    float normal[3];

    vector<float> radius;
    vector<float> y;
    radius.push_back(2);
    y.push_back(4);
    radius.push_back(2.5);
    y.push_back(3.5);
    radius.push_back(2.8);
    y.push_back(3);
    radius.push_back(2.9);
    y.push_back(2.8);
    radius.push_back(3);
    y.push_back(2.5);
    radius.push_back(3.1);
    y.push_back(2);
    radius.push_back(3);
    y.push_back(1.5);
    radius.push_back(2.8);
    y.push_back(1.2);
    radius.push_back(2);
    y.push_back(1.0);
    radius.push_back(1.6);
    y.push_back(1.0);
    radius.push_back(0);
    y.push_back(1);
    radius.push_back(0);
    y.push_back(1);

    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);
    //   glBegin(GL_TRIANGLE_STRIP);
    //   for (int i = 0; i < 360; i++) {
    //     glVertex3f(radius * cos(i * PI / 180), 2, radius * sin(i * PI / 180));
    //     glVertex3f(0, -3, 0);
    //   }
    //   glEnd();

    // glBegin(GL_POINTS);
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i < 360; i += 1) {
        for (int j = 0; j < y.size(); j += 2) {
            calcNormal(radius, y, i, j, normal);
            glNormal3fv(normal);

            glVertex3d(radius[j] * cos(i * PI / 180), y[j], radius[j] * sin(i * PI / 180));
            glVertex3d(radius[j] * cos(i + 1 * PI / 180), y[j], radius[j] * sin(i + 1 * PI / 180));

            glVertex3d(radius[j + 1] * cos(i * PI / 180), y[j + 1], radius[j + 1] * sin(i * PI / 180));
            glVertex3d(radius[j + 1] * cos(i + 1 * PI / 180), y[j + 1], radius[j + 1] * sin(i + 1 * PI / 180));
        }
        // break;
    }
    glEnd();

    glPopMatrix();
    glutSwapBuffers();
}

void resize(int w, int h) {
    glViewport(0, 0, w, h);
    GLfloat fAspect = (GLfloat)w / (GLfloat)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(35.0f, fAspect, 1.0, 100.0);
    //   glOrtho(-5.0, 5.0, 0.0, 5.0, 5.0, -5.0);
    // glOrtho(-w / 2, w / 2, -h / 2, h / 2, 5.0, -5.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0, 0, -50, 0, 0, 0, 0, 1, 0);
}

void setup() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    // Light values and coordinates
    GLfloat lightPos[] = {0, 200, 0, 1};
    GLfloat ambientLight[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat diffuseLight[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat specref[] = {1.0f, 1.0f, 1.0f, 1.0f};

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    // glDepthRange(0.0, 20.0);
    glEnable(GL_DEPTH_TEST);

    // Enable lighting
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);

    // Setup light 0
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specref);

    // Position and turn on the light
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glEnable(GL_LIGHT0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
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
