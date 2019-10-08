#include <gl/glut.h>
#include <stdio.h>
#include "structs.h"
#include "midpoint.h"
#include "scan.h"
#include "transformation.h"

// Set window size variables
int windowWidth = 1600;
int windowHeight = 900;

// Set maximum number of points that can be placed
int currentPoints;
int currentPolygons = 0;
struct Polygon polygons[MAX_POLYGONS];

char leftClicked = 0;
char rightClicked = 0;
char* mode = "Plotting";
char command[20];

struct Point* selectedPoint = 0;
struct Polygon* selectedPolygon = 0;

void init(void) {
	// set background to white
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-windowWidth/2, windowWidth/2, -windowHeight/2, windowHeight/2);
	glMatrixMode(GL_MODELVIEW);
}

// Main drawing routine. Called repeatedly by GLUT's main loop
void display(void) {
	int i;
	int j;
	int x1;
	int y1;
	int x2;
	int y2;
	int tempX;
	int tempY;
	//Clear the screen and set our initial view matrix
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Draw quadrants
	glPointSize(1);
	glColor3d(0.0, 0.0, 255.0);
	glBegin(GL_LINES);
	glVertex2i(-windowWidth/2, 0);
	glVertex2i(windowWidth/2, 0);
	glVertex2i(0, -windowHeight/2);
	glVertex2i(0, windowHeight/2);
	glEnd();
	// Iterate through each polygon
	for (i = 0; i <= currentPolygons; i++) {
		// Fill simple polygons
		glPointSize(1);
		glColor3d(255.0, 128.0, 0.0);
		checkIntersections(&(polygons[i]));
		if (polygons[i].isSimple == 1 && polygons[i].complete == 1) {
			glBegin(GL_POINTS);
			fillPolygon(polygons[i]);
			glEnd();
		}
		// Draw Lines; Draw only if more than one point exists
		glPointSize(1);
		// Check for intersections in polygon
		if (polygons[i].isSimple == -1) {
			glColor3f(255.0, 0.0, 0.0);
		}
		else {
			glColor3f(0.0, 0.0, 0.0);
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
		glColor3f(0.0, 255.0, 0.0);
		glBegin(GL_POINTS);
		for (j = 0; j < currentPoints; j++) {
			int x = polygons[i].vertices[j].x;
			int y = polygons[i].vertices[j].y;	
			glVertex2i(x, y);
		}
		glEnd();
	}
	// Highlight any selected point if any
	if (selectedPoint != 0) {
		glPointSize(10);
		glColor4f(255.0, 255.0, 0.0, 0.5);
		glBegin(GL_POINTS);
		glVertex2i(selectedPoint->x, selectedPoint->y);
		glEnd();
	}
	glutSwapBuffers();
}

void mouseInput(int button, int state, int x, int y) {
	int newX = x - windowWidth/2;
	int newY = -y + windowHeight/2;
	// When left click is pressed
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (mode == "Plotting") {
			// Check if point or polygon limit has been reached
			if (currentPoints == MAX_POINTS || currentPolygons == MAX_POLYGONS) {
				return;
			}
			// Set x,y coordinates of created point
			polygons[currentPolygons].vertices[currentPoints].x = newX;
			polygons[currentPolygons].vertices[currentPoints].y = newY;
			// Increment total number of points
			polygons[currentPolygons].numPoints++;
			currentPoints++;
			if (currentPoints > 1) {
				polygons[currentPolygons].lines[polygons[currentPolygons].numLines].a = &polygons[currentPolygons].vertices[currentPoints-2];
				polygons[currentPolygons].lines[polygons[currentPolygons].numLines].b = &polygons[currentPolygons].vertices[currentPoints-1];
				polygons[currentPolygons].numLines++;
			}
		}
		else {
			selectedPoint = checkForPoint(polygons, currentPolygons, newX, newY);
			selectedPolygon = checkForPolygon(polygons, currentPolygons, selectedPoint);
		}
		glutPostRedisplay();
	}
	// When right click is pressed
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		if (mode == "Plotting") {
			currentPoints = polygons[currentPolygons].numPoints;
			if (currentPoints < 3) {
				return;
			}
			polygons[currentPolygons].complete = 1;
			polygons[currentPolygons].lines[polygons[currentPolygons].numLines].a = &polygons[currentPolygons].vertices[currentPoints-1];
			polygons[currentPolygons].lines[polygons[currentPolygons].numLines].b = &polygons[currentPolygons].vertices[0];
			polygons[currentPolygons].numLines++;
			polygons[currentPolygons].isSimple = 1;
			// Start next polygon creation
			currentPolygons++;
			if (currentPolygons == MAX_POLYGONS) {
				return;
			}
		}
		else {
			selectedPoint->x = newX;
			selectedPoint->y = newY;
		}
		glutPostRedisplay();
	}
}

void keyInput(unsigned char key, int x, int y) {
	int xVal = 0;
	int yVal = 0;
	int angle = 0;
	switch(key) {
	case 'd':
		currentPolygons -= removeNonSimple(polygons);
		rearrangeArr(polygons, currentPolygons);
		glutPostRedisplay();
		break;
	case 'p':
		mode = "Plotting";
		glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
		selectedPoint = 0;
		break;
	case 't':
		mode = "Transforming";
		glutSetCursor(GLUT_CURSOR_CROSSHAIR);
		selectedPoint = 0;
		break;
	case 'q':
		if (mode != "Transforming") {
			printf("Please set mode to Transform.\n");
			break;
		}
		if (selectedPolygon == 0) {
			printf("Please select a polygon by clicking one of its points in Transformation Mode.\n");
			break;
		}
		printf("Enter a transformation command: ");
		scanf("%s", command);
		// Translation
		if (command[0] == 't') {
			printf("Enter x and y factor: ");
			scanf("%d %d", &xVal, &yVal);
			translation(selectedPolygon, xVal, yVal);
		}
		// Scale
		else if (command[0] == 's') {
			printf("Enter x and y factor: ");
			scanf("%d %d", &xVal, &yVal);
			scale(selectedPolygon, xVal, yVal);
		}
		// Shear
		else if (command[0] == 'h') {
			printf("Enter x and y factor: ");
			scanf("%d %d", &xVal, &yVal);
			shear(selectedPolygon, xVal, yVal);
		}
		// Rotation with respect to the origin
		else if (command[0] == 'r') {
			printf("Enter rotation angle: ");
			scanf("%d", &angle);
			rotation(selectedPolygon, angle);
		}
		// Reflection over y = -x
		else if (command[0] == 'm') {
			reflection(selectedPolygon);
		}
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
	glutInitWindowPosition (150, 100);
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