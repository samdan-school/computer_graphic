#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <string.h>
#define PI 3.14159265

using namespace std;

vector<vector<float>> vertex3d;
vector<vector<int>> vertexFace;

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void ReduceToUnit(float vector[3])
{
	float length;

	// Calculate the length of the vector
	length = (float)sqrt((vector[0] * vector[0]) +
						 (vector[1] * vector[1]) +
						 (vector[2] * vector[2]));

	// Keep the program from blowing up by providing an exceptable
	// value for vectors that may calculated too close to zero.
	if (length == 0.0f)
		length = 1.0f;

	// Dividing each element by the length will result in a
	// unit normal vector.
	vector[0] /= length;
	vector[1] /= length;
	vector[2] /= length;
}

void calcNormal(float v[3][3], float out[3])
{
	float v1[3], v2[3];
	static const int x = 0;
	static const int y = 1;
	static const int z = 2;

	// Calculate two vectors from the three points
	v1[x] = v[0][x] - v[1][x];
	v1[y] = v[0][y] - v[1][y];
	v1[z] = v[0][z] - v[1][z];

	v2[x] = v[1][x] - v[2][x];
	v2[y] = v[1][y] - v[2][y];
	v2[z] = v[1][z] - v[2][z];

	// Take the cross product of the two vectors to get
	// the normal vector which will be stored in out
	out[x] = v1[y] * v2[z] - v1[z] * v2[y];
	out[y] = v1[z] * v2[x] - v1[x] * v2[z];
	out[z] = v1[x] * v2[y] - v1[y] * v2[x];

	// Normalize the vector (shorten length to one)
	ReduceToUnit(out);
}

bool is_read = true;

bool ReadFromFile(const char *path)
{
	FILE *file = fopen(path, "r");
	if (file == NULL)
	{
		printf("Impossible to open the file !\n");
		return false;
	}
	while (1)
	{
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.}
		if (strcmp(lineHeader, "v") == 0)
		{
			float x, y, z;
			vector<float> temp;
			fscanf(file, "%f %f %f\n", &x, &y, &z);
			temp.push_back(x);
			temp.push_back(y);
			temp.push_back(z);
			vertex3d.push_back(temp);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			int x, y, z;
			vector<int> temp;
			fscanf(file, "%d %d %d\n", &x, &y, &z);
			temp.push_back(x);
			temp.push_back(y);
			temp.push_back(z);
			vertexFace.push_back(temp);
		}
	}
}

void displayMe(void);
void SpecialKeys(int key, int x, int y)
{
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

void displayMe(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	glColor3f(1, 0, 0);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < vertexFace.size(); i++)
	{
		glVertex3f(vertex3d[vertexFace[i][0] - 1][0], vertex3d[vertexFace[i][0] - 1][1], vertex3d[vertexFace[i][0] - 1][2]);
		glVertex3f(vertex3d[vertexFace[i][1] - 1][0], vertex3d[vertexFace[i][1] - 1][1], vertex3d[vertexFace[i][1] - 1][2]);
		glVertex3f(vertex3d[vertexFace[i][2] - 1][0], vertex3d[vertexFace[i][2] - 1][1], vertex3d[vertexFace[i][2] - 1][2]);
	}
	glEnd();

	glPopMatrix();
	glutSwapBuffers();
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	GLfloat fAspect = (GLfloat)w / (GLfloat)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// gluPerspective(35.0f, fAspect, 1.0, 40.0);
	glOrtho(-40.0, 40.0, -40.0, 40.0, 40.0, -40.0);
	// glOrtho(-w / 2, w / 2, -h / 2, h / 2, 5.0, -5.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void setup()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	if (is_read)
	{
		ReadFromFile("./bunny.obj");
		is_read = false;
		cout << is_read << endl;
	}
}

int main(int argc, char **argv)
{
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
