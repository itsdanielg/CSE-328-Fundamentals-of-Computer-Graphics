#include <GL/glut.h>
#include <math.h>

#define X .525731112119133606
#define Z .850650808352039932

GLsizei windowWidth = 1600;
GLsizei windowHeight = 900;
float aspectRatio;
float *v1;
float *v2;
float *v3;

void drawTriangle(float *v1, float *v2, float *v3, float offset, int xRad, int yRad, int zRad);
void subdivide(float *v1, float *v2, float *v3, long depth, float offset, int xRad, int yRad, int zRad);
void normalize(float v[3]);

void init(void) {
	aspectRatio =  (float)windowWidth/windowHeight;
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(90, aspectRatio, 0.001, 1000.0);
	glMatrixMode(GL_MODELVIEW);
}

void display(void) {

	int i;

	GLfloat vdata[12][3] = {
		{-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},
		{0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},
		{Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0}
	};

	static GLuint icosahedron[20][3] = {
		{1, 4, 0}, {4, 9, 0}, {4, 5, 9}, {8, 5, 4}, {1, 8, 4},
		{1, 10, 8}, {10, 3, 8}, {8, 3, 5}, {3, 2, 5}, {3, 7, 2},
		{3, 10, 7}, {10, 6, 7}, {6, 11, 7}, {6, 0, 11}, {6, 1, 0},
		{10, 1, 6}, {11, 0, 9}, {2, 11, 9}, {5, 2, 9}, {11, 2, 7}
	};

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Set camera position and look at origin
	gluLookAt(1.0, 4.0, 6.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 1.0);
	for (i = 0; i < 20; i++) {
		v1 = &vdata[icosahedron[i][0]][0];
		v2 = &vdata[icosahedron[i][1]][0];
		v3 = &vdata[icosahedron[i][2]][0];
		subdivide(v1, v2, v3, 0, -5, 3, 2, 1);
		subdivide(v1, v2, v3, 1, 0, 2, 4, 1);
		subdivide(v1, v2, v3, 2, 7, 4, 2, 3);
	}
	glEnd();

	glFlush();
}

void drawTriangle(float *v1, float *v2, float *v3, float offset, int xRad, int yRad, int zRad) {
	float one[3] = {v1[0] * xRad + offset, v1[1] * yRad, v1[2] * zRad};
	float two[3] = {v2[0] * xRad + offset, v2[1] * yRad, v2[2] * zRad};
	float three[3] = {v3[0] * xRad + offset, v3[1] * yRad, v3[2] * zRad};
	float oneNormal[3] = {v1[0] / xRad + offset, v1[1] / yRad, v1[2] / zRad};
	float twoNormal[3] = {v2[0] / xRad + offset, v2[1] / yRad, v2[2] / zRad};
	float threeNormal[3] = {v3[0] / xRad + offset, v3[1] / yRad, v3[2] / zRad};
	glNormal3fv(oneNormal);
	glVertex3fv(one);
	glNormal3fv(twoNormal);
	glVertex3fv(two);
	glNormal3fv(threeNormal);
	glVertex3fv(three);
}

void subdivide(float *v1, float *v2, float *v3, long depth, float offset, int xRad, int yRad, int zRad) {
	GLfloat v12[3], v23[3], v31[3];
	GLint i;
	if (depth == 0) {
		drawTriangle(v1, v2, v3, offset, xRad, yRad, zRad);
		return;
	}
	for (i = 0; i < 3; i++) {
		v12[i] = (v1[i] + v2[i]) / 2.0;
		v23[i] = (v2[i] + v3[i]) / 2.0;
		v31[i] = (v3[i] + v1[i]) / 2.0;
	}
	normalize(v12);
	normalize(v23);
	normalize(v31);
	subdivide(v1, v12, v31, depth-1, offset, xRad, yRad, zRad);
	subdivide(v2, v23, v12, depth-1, offset, xRad, yRad, zRad);
	subdivide(v3, v31, v23, depth-1, offset, xRad, yRad, zRad);
	subdivide(v12, v23, v31, depth-1, offset, xRad, yRad, zRad);
}

void normalize(float v[3]) {
	GLfloat d = sqrt(v[0] * v[0] + v[1]  * v[1] + v[2] * v[2]);
	if (d == 0.0) {
		return;
	}
	v[0] /= d;
	v[1] /= d;
	v[2] /= d;
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Homework 2 (Part 5)");

	init();

	glutDisplayFunc(display);

	glutMainLoop();
}