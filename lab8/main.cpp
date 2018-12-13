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

  glBegin(GL_QUADS);
  for(int i = 0; i < faces.size(); ++i) {
    // calcNormal(faces[i], normal);
    // glNormal3fv(normal);
    int j = 0;    
    glNormal3f(normal[faces[i][j + 2] - 1][0],
               normal[faces[i][j + 2] - 1][1],
               normal[faces[i][j + 2] - 1][2]);
    glVertex3f(vertices[faces[i][j] - 1][0],
               vertices[faces[i][j] - 1][1],
               vertices[faces[i][j] - 1][2]); 
               
    j += 3;
    glNormal3f(normal[faces[i][j] - 1][0],
               normal[faces[i][j] - 1][1],
               normal[faces[i][j] - 1][2]);
    glVertex3f(vertices[faces[i][j] - 1][0],
               vertices[faces[i][j] - 1][1],
               vertices[faces[i][j] - 1][2]); 
               
    j += 3;    
    glNormal3f(normal[faces[i][j + 2] - 1][0],
               normal[faces[i][j + 2] - 1][1],
               normal[faces[i][j + 2] - 1][2]);
    glVertex3f(vertices[faces[i][j] - 1][0],
               vertices[faces[i][j] - 1][1],
               vertices[faces[i][j] - 1][2]);  
               
    j += 3;    
    glNormal3f(normal[faces[i][j + 2] - 1][0],
               normal[faces[i][j + 2] - 1][1],
               normal[faces[i][j + 2] - 1][2]);           
    glVertex3f(vertices[faces[i][j] - 1][0],
               vertices[faces[i][j] - 1][1],
               vertices[faces[i][j] - 1][2]); 
  }
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
    cout << faces.size();
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
  glEnable(GL_TEXTURE_2D);
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