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
  if (key == GLUT_KEY_UP) xRot -= 5.0f;

  if (key == GLUT_KEY_DOWN) xRot += 5.0f;

  if (key == GLUT_KEY_LEFT) yRot -= 5.0f;

  if (key == GLUT_KEY_RIGHT) yRot += 5.0f;

  xRot = (GLfloat)((const int)xRot % 360);
  yRot = (GLfloat)((const int)yRot % 360);

  // Refresh the Window
  glutPostRedisplay();
}

void displayMe(void) {
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
  float x = 0.0;
  glBegin(GL_QUAD_STRIP);
  for (int i = 0; i < 360; i += 2) {
    x = 2;

    glVertex3d(x * cos(i * PI / 180), 4, x * sin(i * PI / 180));
    glVertex3d(x + 1 * cos(i + 1 * PI / 180), 4, x * sin(i + 1 * PI / 180));

    x = 2.5;
    glVertex3d(x * cos(i * PI / 180), 3.5, x * sin(i * PI / 180));

    x = 2.8;
    glVertex3d(x * cos(i * PI / 180), 3, x * sin(i * PI / 180));

    x = 2.9;
    glVertex3d(x * cos(i * PI / 180), 2.8, x * sin(i * PI / 180));

    x = 3;
    glVertex3d(x * cos(i * PI / 180), 2.5, x * sin(i * PI / 180));

    x = 3.1;
    glVertex3d(x * cos(i * PI / 180), 2, x * sin(i * PI / 180));

    x = 3;
    glVertex3d(x * cos(i * PI / 180), 1.5, x * sin(i * PI / 180));

    x = 2.8;
    glVertex3d(x * cos(i * PI / 180), 1.2, x * sin(i * PI / 180));

    x = 2;
    glVertex3d(x * cos(i * PI / 180), 1.0, x * sin(i * PI / 180));

    x = 1.6;
    glVertex3d(x * cos(i * PI / 180), 1.0, x * sin(i * PI / 180));

    x = 0;
    glVertex3d(x * cos(i * PI / 180), 1, x * sin(i * PI / 180));
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
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(600, 600);
  glutInitWindowPosition(200, 50);
  glutCreateWindow("3d");
  glutReshapeFunc(resize);
  glutDisplayFunc(displayMe);
  glutSpecialFunc(SpecialKeys);
  //   setup();
  glutMainLoop();
  return 0;
}
