#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#ifndef CALLBACK
#define CALLBACK
#endif

GLuint startList;

void CALLBACK errorCallback(GLenum errorCode) {
	const GLubyte* estring;
	estring = gluErrorString(errorCode);
	fprintf(stderr, "Quadric Error: %s\n", estring);
	exit(0);
}

void init(void) {
	GLUquadricObj* qobj;
	GLfloat mat_ambient[] = {0.5, 0.5, 0.5, 1.0};
	GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat mat_shininess[] = {50.0};
	GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
	GLfloat model_ambient[] = {0.5, 0.5, 0.5, 1.0};

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	startList = glGenLists(4);
	qobj = gluNewQuadric();
	gluQuadricCallback(qobj, GLU_ERROR, errorCallback);

	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	glNewList(startList+1, GL_COMPILE);
	gluSphere(qobj, 1, 50, 50);
	glEndList();

	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_FLAT);
	glNewList(startList+2, GL_COMPILE);
	gluCylinder(qobj, 0.7, 0.7, 1.5, 25, 25);
	glEndList();

	gluQuadricDrawStyle(qobj, GLU_LINE);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	glNewList(startList+3, GL_COMPILE);
	gluCylinder(qobj, 0.8, 0.0, 1.5, 30, 30);
	glEndList();

}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glTranslatef(-1.0, -1.0, 0.0);
	glCallList(startList);

	glShadeModel(GL_FLAT);
	glTranslatef(0.0, 2.0, 0.0);
	glPushMatrix();
	glRotatef(300.0, 1.0, 0.0, 0.0);
	glCallList(startList+1);
	glPopMatrix();

	glShadeModel(GL_FLAT);
	glColor3f(0.0, 1.0, 1.0);
	glTranslatef(1.0, -2.7, 0.0);
	glRotatef(300.0, 1.0, 0.0, 0.0);
	glCallList(startList+2);

	glShadeModel(GL_SMOOTH);
	glColor3f(1.0, 1.0, 0.0);
	glTranslatef(1.2, 4.5, 0.0);
	glCallList(startList+3);
	
	glPopMatrix();
	glFlush();
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <=h) {
		glOrtho(-2.5, 2.5, -2.5*(GLfloat)h/(GLfloat)2, 2.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
	}
	else {
		glOrtho(-2.5*(GLfloat)w/(GLfloat)h, 2.5*(GLfloat)w/(GLfloat)h, -2.5, 2.5, -10.0, 10.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) {
	switch(key) {
	case 27:
		exit(0);
		break;
	}
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1000, 900);
	glutCreateWindow("Homework 2 (Part 4)");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
}