#include <GL/glut.h>
#include <math.h>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

void drawTorus(int innerRadius, int outerRadius, int nsides, int rings);

GLsizei windowWidth = 1600;
GLsizei windowHeight = 900;
float aspectRatio;

GLuint torusObject;
float xRotate = 0;
float yRotate = 0;
float zRotate = 0;
float status;

// Function to draw torus and its normals
void drawTorus(float innerRadius, float outerRadius, int nsides, int rings) {
   int i, j, k;
   float s, t;
   double xPos, yPos, zPos;
   double twoPI = 2 * (double)M_PI;
   
   glBegin(GL_QUAD_STRIP);
   for (i = 0; i < nsides; i++) {
      for (j = 0; j <= rings; j++) {
         for (k = 1; k >= 0; k--) {
            s = (i + k) % nsides + 0.5;
            t = j % (rings + 1);
            xPos = (outerRadius + innerRadius * cos(s * twoPI / nsides)) * cos(t * twoPI / rings);
            yPos = (outerRadius + innerRadius * cos(s * twoPI / nsides)) * sin(t * twoPI / rings);
            zPos = innerRadius * sin(s * twoPI / nsides);
            glVertex3f(xPos, yPos, zPos);
			glNormal3f(xPos, yPos, zPos);
         }
      }
   }
   glEnd();
}

void init(void) {
	// Set lighting
	GLfloat mat_ambient[] = {0.5, 0.5, 0.5, 1.0};
	GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat mat_shininess[] = {50.0};
	GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
	GLfloat model_ambient[] = {0.5, 0.5, 0.5, 1.0};

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	
	// Create display list for torus
	torusObject = glGenLists(1);
	glNewList(torusObject, GL_COMPILE);
	drawTorus(0.5, 2, 32, 32);
	glEndList();

	// Set black background with smooth lighting
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	// Switch between wireframe and solid
	if (status < 180) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	// Make torus
	glColor3f(1.0, 1.0, 1.0);
	glRotatef(xRotate, 1.0, 0.0, 0.0);
	glRotatef(yRotate, 0.0, 1.0, 0.0);
	glRotatef(zRotate, 0.0, 0.0, 1.0);
	glCallList(torusObject);
	
	glPopMatrix();
	glutSwapBuffers();
}

// Animate camera
void idle() {
	status += 0.2;
	xRotate += 0.1;
	yRotate += 0.2;
	zRotate += 0.05;
	if (xRotate >= 360) {
		xRotate = 0;
	}
	if (yRotate >= 360) {
		yRotate = 0;
	}
	if (zRotate >= 360) {
		zRotate = 0;
	}
	if (status > 360) {
		status = 0;
	}
	glutPostRedisplay();
}

void reshape(int width, int height) {
	windowWidth = width;
	windowHeight = height;
	aspectRatio = (float) windowWidth / windowHeight;

	glViewport(0, 0, (GLsizei) width, (GLsizei) height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, aspectRatio, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Set camera position and look at origin
	gluLookAt(0.0, 0.0, 4, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Homework 2 (Part 6)");

	init();

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);

	glutMainLoop();
}