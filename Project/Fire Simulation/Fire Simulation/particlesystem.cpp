#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "globalvar.h"

#define MAX_PARTICLES 5000

float emissionXMin = -1.0;
float emissionXMax = 1.0;
float emissionYMin = -1.0;
float emissionYMax = 1.0;
float emissionZMin = -1.0;
float emissionZMax = 1.0;

float minVel = 0.05;
float maxVel = 0.2;
float maxTemp = 100.0;
float maxLifespan = 100.0;

int id;
Particle particles[MAX_PARTICLES];

int ParticleSystem::generateInt(int min, int max) {
	int num = (rand() % (max - min + 1)) + min;
	return num;
}

float ParticleSystem::generateFloat(float min, float max) {
	float range = rand() / (float) RAND_MAX;
	return min + range * (max - min);
}

void ParticleSystem::resetSystem() {
	int i = 0;
	id = 0;
	for (i = 0; i < MAX_PARTICLES; i++) {
		particles[i].status = 0;
		particles[i].point.xPosOne = 0;
		particles[i].point.yPosOne = 0;
		particles[i].point.zPosOne = 0;
		particles[i].point.xPosTwo = 0;
		particles[i].point.yPosTwo = 0;
		particles[i].point.zPosTwo = 0;
		particles[i].velocity = 0;
		particles[i].red = 0.0;
		particles[i].green = 0.0;
		particles[i].blue = 0.0;
		particles[i].temperature = 0;	
		particles[i].age = 0;
		particles[i].lifespan = 0;
		particles[i].id = 0;
	}
}

void ParticleSystem::createParticles() {
	int i = 0;
	emissionXMin = -1.0 * emitterRadius;
	emissionXMax = 1.0 * emitterRadius;
	emissionYMin = -1.0 * emitterRadius;
	emissionYMax = 1.0 * emitterRadius;
	emissionZMin = -1.0 * emitterRadius;
	emissionZMax = 1.0 * emitterRadius;
	for (i = 0; i < MAX_PARTICLES; i++) {
		if (particles[i].status == 0) {
			id++;
			particles[i].point.xPosOne = generateInt(emissionXMin, emissionXMax);
			particles[i].point.yPosOne = generateInt(emissionYMin, emissionYMax);
			particles[i].point.zPosOne = generateInt(emissionZMin, emissionZMax);
			particles[i].point.xPosTwo = particles[i].point.xPosOne + 0.1;
			particles[i].point.yPosTwo = particles[i].point.yPosOne;
			particles[i].point.zPosTwo = particles[i].point.zPosOne;
			particles[i].velocity = generateFloat(minVel, maxVel);
			particles[i].red = generateFloat(0, 255)/255.0;
			particles[i].green = generateFloat(0, 255)/255.0;
			particles[i].blue = generateFloat(0, 255)/255.0;
			particles[i].temperature = maxTemp;	
			particles[i].age = 0;
			particles[i].lifespan = generateInt(0, maxLifespan);
			particles[i].id = id;
			particles[i].status = 1;
			break;
		}
	}
}

void ParticleSystem::modifyParticles() {
	int i = 0;
	for (i = 0; i < MAX_PARTICLES; i++) {
		if (particles[i].status == 1) {
			// X Movement
			if (generateInt(0, 2) == 0) {
				particles[i].point.xPosOne += particles[i].velocity;
				particles[i].point.xPosTwo += particles[i].velocity;
			}
			else {
				particles[i].point.xPosOne -= particles[i].velocity;
				particles[i].point.xPosTwo -= particles[i].velocity;
			}
			// Z Movement
			if (generateInt(0, 2) == 0) {
				particles[i].point.zPosOne += particles[i].velocity;
				particles[i].point.zPosTwo += particles[i].velocity;
			}
			else {
				particles[i].point.zPosOne -= particles[i].velocity;
				particles[i].point.zPosTwo -= particles[i].velocity;
			}
			// Y Movement
			particles[i].point.yPosOne += particles[i].velocity;
			particles[i].point.yPosTwo += particles[i].velocity;
			// Lower lifespan
			particles[i].lifespan--;
			particles[i].age++;
			// Kill particle if lifespan ends
			if (particles[i].lifespan < 0) {
				particles[i].status = 0;
			}
		}
	}
}

void ParticleSystem::step() {
	// Create new particle
	int i;
	for (i = 0; i < emitterRate; i++) {
		createParticles();
	}
	// Modify particles as necessary
	modifyParticles();
}

void ParticleSystem::drawScene() {
	int i = 0;
	glLineWidth(2);
	glBegin(GL_LINES);
	for (i = 0; i < MAX_PARTICLES; i++) {
		if (particles[i].status == 1) {
			glColor3f(particles[i].red, particles[i].green, particles[i].blue);
			glVertex3f(particles[i].point.xPosOne, particles[i].point.yPosOne, particles[i].point.zPosOne);
			glVertex3f(particles[i].point.xPosTwo, particles[i].point.yPosTwo, particles[i].point.zPosTwo);
		}
	}
	glEnd();
}