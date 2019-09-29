#include <gl/glut.h>
#include <stdio.h>
#include "midpoint.h"

// Set window size variables
int windowWidth = 720;
int windowHeight = 480;

// Set maximum number of points that can be placed
int maxPoints = 100;
int currentPoints = 0;
int currentPolygons = 0;
int pointArray[100][2];
char leftClicked = 0;
char rightClicked = 0;

int x1;
int y1;
int x2;
int y2;


void init(void) {
	// set background to white
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);
	glMatrixMode(GL_MODELVIEW);
}

// Main drawing routine. Called repeatedly by GLUT's main loop
void display(void) {
	int i;
	int tempX;
	int tempY;
	int slope;
	//Clear the screen and set our initial view matrix
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Draw Lines; Draw only if more than one point exists
	glPointSize(1);
	glColor3f(0.0, 0.0, 0.0);
	if (currentPoints > 1) {
		glBegin(GL_POINTS);
		for (i = 0; i < currentPoints - 1; i++) {
			// Set values of x1, y1, x2, y2
			x1 = pointArray[i][0];
			y1 = pointArray[i][1];
			x2 = pointArray[i+1][0];
			y2 = pointArray[i+1][1];
			
			// Switch points if x2 < x1
			if (x2 < x1) {
				tempX = x2;
				tempY = y2;
				x2 = x1;
				y2 = y1;
				x1 = tempX;
				y1 = tempY;
			}
			midpointAlg(x1, y1, x2, y2);
		}
		if (rightClicked == 1) {
			rightClicked = 0;
			x1 = pointArray[0][0];
			y1 = pointArray[0][1];
			x2 = pointArray[i][0];
			y2 = pointArray[i][1];
			
			// Switch points if x2 < x1
			if (x2 < x1) {
				tempX = x2;
				tempY = y2;
				x2 = x1;
				y2 = y1;
				x1 = tempX;
				y1 = tempY;
			}
			midpointAlg(x1, y1, x2, y2);
		}
		glEnd();
	}
	// Draw Points
	glPointSize(5);
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	for (i = 0; i < currentPoints; i++) {
		glVertex2i(pointArray[i][0], pointArray[i][1]);
	}
	glEnd();
	glutSwapBuffers();
}

void mouseInput(int button, int state, int x, int y) {
	// When left click is pressed
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		// Check if point limit has been reached
		if (currentPoints == maxPoints) {
			return;
		}
		if (leftClicked == 1) {
			return;
		}
		// Set x,y coordinates of created point
		pointArray[currentPoints][0] = x;
		pointArray[currentPoints][1] = windowHeight - y;	// Flip the value due to y starting from top row
		// Increment total number of points
		currentPoints++;
		glutPostRedisplay();
	}
	// When right click is pressed
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		if (currentPoints < 3) {
			return;
		}
		leftClicked = 1;
		rightClicked = 1;
		glutPostRedisplay();
	}
	
}

// Entry point - GLUT setup and initialization
int main(int argc, char** argv) {
	// Initialization
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (windowWidth, windowHeight);
	glutInitWindowPosition (700, 300);
	// Window Creation
	glutCreateWindow("Homework 1");
	// Function to display
	glutDisplayFunc(display);
	// Mouse Inputs
	glutMouseFunc(mouseInput);
	init();
	// Enter Main Loop
	glutMainLoop();
	return 0;
}