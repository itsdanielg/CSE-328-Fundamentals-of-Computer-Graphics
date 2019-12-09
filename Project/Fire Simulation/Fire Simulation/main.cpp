#pragma once

#include <GL/glui.h>
#include <GL/glut.h>
#include "globalvar.h"
#include "gui.h"
#include "noise.h"

////////// INIT VARIABLES //////////
int mainWindow;
int windowWidth = 1600;
int windowHeight = 950;
float aspectRatio = aspectRatio = (float) windowWidth / windowHeight;
int windowPosX = (1920 - windowWidth) / 2;
int windowPosY = (1080 - windowHeight) / 2;
FireSystem fireSystem;

bool drawFrame = false;
int timeSinceStart = 0;
int timeSinceStepUpdate = 0;
int timeStepUpdate = 0;
int timeSinceFrameUpdate = 0;
int timeFrameUpdate = 0;
int deltaTime = 0;

void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	//glEnable(GL_DEPTH_TEST);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (drawFrame) {
		fireSystem.drawScene();
		drawFrame = false;
		glutSwapBuffers();
	}
	if (sysStatus == 0) {
		fireSystem.drawScene();
		glutSwapBuffers();
	}
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
		timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
		timeSinceStepUpdate = timeSinceStart - timeStepUpdate;
		if (timeSinceStepUpdate / (1000/timingStepsPerSec) >= 1) {
			deltaTime = timeSinceStart - timeStepUpdate;
			timeStepUpdate = timeSinceStart;
			fireSystem.step(deltaTime);
		}
		timeSinceFrameUpdate = timeSinceStart - timeFrameUpdate;
		if (timeSinceFrameUpdate / (1000/timingFramesPerSec) >= 1) {
			timeFrameUpdate = timeSinceStart;
			frameCount++;
			glui->sync_live();
			drawFrame = true;
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