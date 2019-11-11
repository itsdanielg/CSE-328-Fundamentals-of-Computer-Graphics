#pragma once

#include <GL/glui.h>
#include <GL/glut.h>
#include "globalvar.h"
#include "gui.h"

////////// INIT VARIABLES //////////
int mainWindow;
int windowWidth = 1600;
int windowHeight = 950;
float aspectRatio = aspectRatio = (float) windowWidth / windowHeight;
int windowPosX = (1920 - windowWidth) / 2;
int windowPosY = (1080 - windowHeight) / 2;
FireSystem fireSystem;

int stepCounter = 0;
int frameCounter = 0;

void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	fireSystem.drawScene();
	glutSwapBuffers();
}

void reshape(int width, int height) {
	windowWidth = width;
	windowHeight = height;
	if (windowWidth < 1000) {
		windowWidth = 1000;
		glutReshapeWindow(windowWidth, windowHeight);
	}
	if (windowHeight < 950) {
		windowHeight = 950;
		glutReshapeWindow(windowWidth, windowHeight);
	}
	glViewport(0, 0, (GLsizei)windowWidth, (GLsizei)windowHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(cameraFOV, cameraAspect, cameraNear, cameraFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cameraPosX, cameraPosY, cameraPosZ, cameraLookAtX, cameraLookAtY, cameraLookAtZ, 0.0, 1.0, 0.0);
}

void idle() {
	if (glutGetWindow() != mainWindow) {
		glutSetWindow(mainWindow);
	}
	if (sysStatus == 1) {
		stepCounter++;
		frameCounter++;
		if (stepCounter > 333/timingStepsPerSec) {
			fireSystem.step();
			stepCounter = 0;
		}
		if (frameCounter > 333/timingFramesPerSec) {
			frameCount++;
			glui->sync_live();
			frameCounter = 0;
		}
	}
	reshape(windowWidth, windowHeight);
	glutPostRedisplay();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(windowPosX, windowPosY);
	glutInitWindowSize(windowWidth, windowHeight);

	mainWindow = glutCreateWindow("Fire Simulation");
	GLUI_Master.set_glutDisplayFunc(display);
	GLUI_Master.set_glutReshapeFunc(reshape);
	GLUI_Master.set_glutIdleFunc(idle);
	
	init();
	resetVar();
	initGlui();
	adjustGlui();

	fireSystem.resetSystem();

	glutMainLoop();
}