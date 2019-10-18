#include <GL/glut.h>

GLsizei windowWidth = 1600;
GLsizei windowHeight = 900;

void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 20.0); // Set viewing frustum at origin
	glMatrixMode(GL_MODELVIEW);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Set camera position and look at origin
	gluLookAt(2.0, 10.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// Make cube
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(-5.0, 0.0, 0.0);
	glScalef(1.0, 2.0, 2.0);
	glutWireCube(3.0);

	// Make tetrahedron
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(8.0, 0.0, 0.0);
	glScalef(2.0, 2.0, 2.0);
	glutWireTetrahedron();

	glFlush();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Homework 2 (Part 1-2)");

	init();

	glutDisplayFunc(display);

	glutMainLoop();
}