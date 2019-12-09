#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "globalvar.h"
#include "noise.h"

#define MAX_PARTICLES 5000

float emissionXMin = -1.0;
float emissionXMax = 1.0;
float emissionYMin = -1.0;
float emissionYMax = 1.0;
float emissionZMin = -1.0;
float emissionZMax = 1.0;

float minVel = 0.001;
float maxVel = 0.005;
float maxTemp = 100.0;
float maxLifespan = 100.0;

int id;
Particle particles[MAX_PARTICLES];

PerlinNoise pn;

int ParticleSystem::generateInt(int min, int max) {
	int num = (rand() % (max - min + 1)) + min;
	return num;
}

float ParticleSystem::generateFloat(float min, float max) {
	float range = rand() / (float) RAND_MAX;
	return min + range * (max - min);
}

void ParticleSystem::resetSystem() {
	int i;
	id = 0;
	for (i = 0; i < MAX_PARTICLES; i++) {
		particles[i].status = 0;
		particles[i].point.xPos = 0;
		particles[i].point.yPos = 0;
		particles[i].point.zPos = 0;
		particles[i].velocity = 0;
		particles[i].noiseX = 0;
		particles[i].noiseY = 0;
		particles[i].red = 0.0;
		particles[i].green = 0.0;
		particles[i].blue = 0.0;
		particles[i].alpha = 0.0;
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
			particles[i].point.xPos = generateFloat(emissionXMin, emissionXMax);
			particles[i].point.yPos = generateFloat(emissionYMin, emissionYMax);
			particles[i].point.zPos = generateFloat(emissionZMin, emissionZMax);
			particles[i].velocity = generateFloat(minVel, maxVel);
			particles[i].noiseX = generateFloat(0, 1);
			particles[i].noiseY = generateFloat(0, 1);
			particles[i].red = generateFloat(0, 255)/255.0;
			particles[i].green = generateFloat(0, 255)/255.0;
			particles[i].blue = generateFloat(0, 255)/255.0;
			particles[i].alpha = 1.0;
			particles[i].temperature = maxTemp;	
			particles[i].age = 0;
			particles[i].lifespan = generateInt(0, maxLifespan);
			particles[i].id = id;
			particles[i].status = 1;
			break;
		}
	}
}

void ParticleSystem::modifyParticles(int deltaTime) {
	int i = 0;
	for (i = 0; i < MAX_PARTICLES; i++) {
		if (particles[i].status == 1) {
			// X Movement
			if (generateInt(0, 2) == 0) {
				particles[i].point.xPos += particles[i].velocity * deltaTime;
			}
			else {
				particles[i].point.xPos -= particles[i].velocity * deltaTime;
			}
			// Z Movement
			if (generateInt(0, 2) == 0) {
				particles[i].point.zPos += particles[i].velocity * deltaTime;
			}
			else {
				particles[i].point.zPos -= particles[i].velocity * deltaTime;
			}
			// Y Movement
			particles[i].point.yPos += particles[i].velocity * deltaTime;
			// Update age
			particles[i].age++;
			// Update alpha
			particles[i].alpha = 1.0 - (particles[i].age/particles[i].lifespan);
			// Kill particle if lifespan ends
			if (particles[i].age >= particles[i].lifespan) {
				particles[i].status = 0;
			}
		}
	}
}

void ParticleSystem::step(int deltaTime) {
	// Create new particle
	int i;
	for (i = 0; i < emitterRate; i++) {
		createParticles();
	}
	// Modify particles as necessary
	modifyParticles(deltaTime);
}

void ParticleSystem::drawScene() {
	for (int i = 0; i < MAX_PARTICLES; i++) {
		if (particles[i].status == 1) {
			float x = particles[i].point.xPos;
			float y = particles[i].point.yPos;
			float z = particles[i].point.zPos;

			float size = particles[i].lifespan - particles[i].age;
			glPointSize(size/2);
			glBegin(GL_POINTS);
			//glColor4f(n, n, n, particles[i].alpha);
			glColor4f(particles[i].red, particles[i].green, particles[i].blue, particles[i].alpha);
			glVertex3f(x, y, z);
			//glVertex3f(particles[i].point.xPos - size, particles[i].point.yPos - size, particles[i].point.zPos);
			//glVertex3f(particles[i].point.xPos - size, particles[i].point.yPos + size, particles[i].point.zPos);
			//glVertex3f(particles[i].point.xPos + size, particles[i].point.yPos + size, particles[i].point.zPos);
			//glVertex3f(particles[i].point.xPos + size, particles[i].point.yPos - size, particles[i].point.zPos);
			glEnd();
		}
	}
	
}