#include <gl/glut.h>
#include <stdio.h>
#include "midpoint.h"
#include "scan.h"
#include "structs.h"

// Set window size variables
int windowWidth = 720;
int windowHeight = 480;

// Set maximum number of points that can be placed
int currentPoints;
int currentPolygons = 0;
struct Polygon polygons[MAX_POLYGONS];

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
	int j;
	int tempX;
	int tempY;
	//Clear the screen and set our initial view matrix
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Iterate through each polygon
	for (i = 0; i <= currentPolygons; i++) {
		// Draw Lines; Draw only if more than one point exists
		glPointSize(1);
		glColor3f(0.0, 0.0, 0.0);
		// Check for intersections in polygon
		checkIntersections(&(polygons[i]));
		if (polygons[i].isSimple == -1) {
			glColor3f(255.0, 0.0, 0.0);
		}
		if (i == MAX_POLYGONS) break;
		currentPoints = polygons[i].numPoints;
		if (currentPoints > 1) {
			glBegin(GL_POINTS);
			for (j = 0; j < currentPoints - 1; j++) {
				// Set values of x1, y1, x2, y2
				x1 = polygons[i].vertices[j].x;
				y1 = polygons[i].vertices[j].y;
				x2 = polygons[i].vertices[j+1].x;
				y2 = polygons[i].vertices[j+1].y;
			
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
			if (polygons[i].complete == 1) {
				x1 = polygons[i].vertices[0].x;
				y1 = polygons[i].vertices[0].y;
				x2 = polygons[i].vertices[j].x;
				y2 = polygons[i].vertices[j].y;
			
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
		for (j = 0; j < currentPoints; j++) {
			int x = polygons[i].vertices[j].x;
			int y = polygons[i].vertices[j].y;	
			glVertex2i(x, y);
		}
		glEnd();
	}
	glutSwapBuffers();
	
}

void mouseInput(int button, int state, int x, int y) {
	// When left click is pressed
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		// Check if point or polygon limit has been reached
		if (currentPoints == MAX_POINTS || currentPolygons == MAX_POLYGONS) {
			return;
		}
		// Set x,y coordinates of created point
		polygons[currentPolygons].vertices[currentPoints].x = x;
		polygons[currentPolygons].vertices[currentPoints].y = windowHeight - y;	// Flip the value due to y starting from top row
		// Increment total number of points
		polygons[currentPolygons].numPoints++;
		currentPoints++;
		if (currentPoints > 1) {
			polygons[currentPolygons].lines[polygons[currentPolygons].numLines].a = polygons[currentPolygons].vertices[currentPoints-2];
			polygons[currentPolygons].lines[polygons[currentPolygons].numLines].b = polygons[currentPolygons].vertices[currentPoints-1];
			polygons[currentPolygons].numLines++;
		}
		glutPostRedisplay();
	}
	// When right click is pressed
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		currentPoints = polygons[currentPolygons].numPoints;
		if (currentPoints < 3) {
			return;
		}
		polygons[currentPolygons].complete = 1;
		polygons[currentPolygons].lines[polygons[currentPolygons].numLines].a = polygons[currentPolygons].vertices[currentPoints-1];
		polygons[currentPolygons].lines[polygons[currentPolygons].numLines].b = polygons[currentPolygons].vertices[0];
		polygons[currentPolygons].numLines++;
		polygons[currentPolygons].isSimple = 1;
		// Start next polygon creation
		currentPolygons++;
		if (currentPolygons == MAX_POLYGONS) {
			return;
		}
		polygons[currentPolygons].numPoints = 0;
		polygons[currentPolygons].complete = 0;
		glutPostRedisplay();
	}
}

void keyInput(unsigned char key, int x, int y) {
	switch(key) {
	case 'd':
		currentPolygons -= removeNonSimple(polygons);
		rearrangeArr(polygons, currentPolygons);
		glutPostRedisplay();
		break;
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
	// Keyboard Inputs
	glutKeyboardFunc(keyInput);
	init();
	// Enter Main Loop
	glutMainLoop();
	return 0;
}