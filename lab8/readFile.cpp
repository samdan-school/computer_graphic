#if !defined(Utilities)
#define Utilities

#define STB_IMAGE_IMPLEMENTATION
#include <GL/glu.h>
#include <GL/glut.h>
#include <string.h>
#include <iostream>
#include <vector>
#include "stb_image.h"

using namespace std;

bool ReadFromFile(const char *path, vector<vector<float>> vertices,
                  vector<vector<float>> texture, vector<vector<float>> normal,
                  vector<vector<int>> faces) {
  FILE *file = fopen(path, "r");
  if (file == NULL) {
    printf("Impossible to open the file !\n");
    return false;
  }
  while (1) {
    char lineHeader[128];
    // read the first word of the line
    int res = fscanf(file, "%s", lineHeader);
    if (res == EOF) break;  // EOF = End Of File. Quit the loop.}
    if (strcmp(lineHeader, "v") == 0) {
      float x, y, z;
      vector<float> temp;
      fscanf(file, "%f %f %f\n", &x, &y, &z);
      temp.push_back(x);
      temp.push_back(y);
      temp.push_back(z);
      vertices.push_back(temp);
    } else if (strcmp(lineHeader, "vt") == 0) {
      float x, y, z;
      vector<float> temp;
      fscanf(file, "%f %f %f\n", &x, &y, &z);
      temp.push_back(x);
      temp.push_back(y);
      temp.push_back(z);
      texture.push_back(temp);
    } else if (strcmp(lineHeader, "vn") == 0) {
      float x, y, z;
      vector<float> temp;
      fscanf(file, "%f %f %f\n", &x, &y, &z);
      temp.push_back(x);
      temp.push_back(y);
      temp.push_back(z);
      normal.push_back(temp);
    } else if (strcmp(lineHeader, "f") == 0) {
      int a1, a2, a3, b1, b2, b3, c1, c2, c3, d1, d2, d3;
      vector<int> temp;
      fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &a1, &a2, &a3, &b1,
             &b2, &b3, &c1, &c2, &c3, &d1, &d2, &d3);
      temp.push_back(a1);
      temp.push_back(a2);
      temp.push_back(a3);
      temp.push_back(b1);
      temp.push_back(b2);
      temp.push_back(b3);
      temp.push_back(c1);
      temp.push_back(c2);
      temp.push_back(c3);
      temp.push_back(d1);
      temp.push_back(d2);
      temp.push_back(d3);
      faces.push_back(temp);
    }
  }
  cout << vertices.size() << endl;
  cout << texture.size() << endl;
  cout << normal.size() << endl;
  cout << faces.size() << endl;
}

void readTexture(const char *path) {
  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  // set the texture wrapping/filtering options (on the currently bound texture
  // object)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // load and generate the texture
  int width, height, nrChannels;
  unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, data);
  } else {
    std::cout << "Failed to load texture" << std::endl;
  }
  stbi_image_free(data);
}

#endif  // Utilities