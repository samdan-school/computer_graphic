#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <vector>

using namespace std;

unsigned int m_texture = -1;

void displayMe(void) {
  m_texture++;
  int w;
  int h;
  int comp;
  unsigned char* image = stbi_load("Texture.jpg", &w, &h, &comp, STBI_rgb);

  cout << sizeof(image) / sizeof(image[0]) << endl;

  cout << w << " : " << h << " : " << comp << " : " << endl;

  if (image == nullptr) throw(std::string("Failed to load texture"));

  glBindTexture(GL_TEXTURE_2D, 1);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE,
               image);

  stbi_image_free(image);

  glClear(GL_COLOR_BUFFER_BIT);
  glPushMatrix();

  glBindTexture(GL_TEXTURE_2D, 1);

  glColor3f(1, 1, 1);

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
}

void setup() {
  glClear(GL_COLOR_BUFFER_BIT);
  glEnable(GL_TEXTURE_2D);
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(600, 600);
  glutInitWindowPosition(200, 50);
  glutCreateWindow("Maya");
  glutReshapeFunc(resize);
  glutDisplayFunc(displayMe);
  setup();
  glutMainLoop();
  return 0;
}