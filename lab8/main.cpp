#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <vector>

#include "readFile.cpp"

using namespace std;

vector<vector<float>> vertices;
vector<vector<float>> texture;
vector<vector<float>> normal;
vector<vector<int>> faces;

bool is_read = false;

void displayMe(void) {
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  glPushMatrix();

  glColor3f(0, 0, 0);

  glBegin(GL_QUAD_STRIP);
  glTexCoord2f(0, 0);
  glVertex3f(0, 0, 0);

  glTexCoord2f(0, 1);
  glVertex3f(10, 0, 0);

  glTexCoord2f(1, 0);
  glVertex3f(0, 10, 0);

  glTexCoord2f(1, 1);
  glVertex3f(10, 10, 0);
  glEnd();

  glPopMatrix();
  glutSwapBuffers();
}

void resize(int w, int h) {
  GLfloat nRange = 25.0f;
  glViewport(0, 0, w, h);
  GLfloat fAspect = (GLfloat)w / (GLfloat)h;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(35.0f, fAspect, 1.0, 1000.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(0, 0, -50, 0, 0, 0, 0, 1, 0);
}

void setup() {
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  if (!is_read) {
    ReadFromFile("./Character.obj", vertices, texture, normal, faces);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nrChannels;
    unsigned char *data =
        stbi_load("./Mapping.jpg", &width, &height, &nrChannels, 0);
    if (data) {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                   GL_UNSIGNED_BYTE, data);
    } else {
      std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    is_read = false;
  }
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

  // Material
  // GLfloat lmodel_ambient[] = {0.2, 0.2, 0.2, 1.0};
  // GLfloat local_view[] = {0.0};

  // glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
  // glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(600, 600);
  glutInitWindowPosition(200, 50);
  glutCreateWindow("Maya");
  glutReshapeFunc(resize);
  glutDisplayFunc(displayMe);
  setup();
  glutMainLoop();
  return 0;
}