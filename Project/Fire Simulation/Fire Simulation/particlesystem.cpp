#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <GL/glut.h>
#include "particle.cpp"

#define MAX_PARTICLES 100

const float emissionXMin = -3.0;
const float emissionXMax = 3.0;
const float emissionYMin = -5.0;
const float emissionYMax = -4.0;
const float emissionZMin = -1.0;
const float emissionZMax = 1.0;

class ParticleSystem {

	public:

	Particle particles[MAX_PARTICLES];

	int generateInt(int min, int max) {
		int num = (rand() % (max - min + 1)) + min;
		return num;
	}

	float generateFloat(float min, float max) {
		float range = rand() / (float) RAND_MAX;
		return min + range * (max - min);
	}

	void resetSystem() {
		int i = 0;
		for (i = 0; i < MAX_PARTICLES; i++) {
			particles[i].status = 0;
			particles[i].point.xPos = 0;
			particles[i].point.yPos = 0;
			particles[i].point.zPos = 0;
			particles[i].velocity = 0;
			particles[i].color[0] = 0.0;
			particles[i].color[1] = 0.0;
			particles[i].color[2] = 0.0;
			particles[i].temperature = 0;	
			particles[i].age = 0;
			particles[i].lifespan = 0;
			particles[i].id = 0;
		}
	}

	void step() {
		int i = 0;
		// Create new particle
		for (i = 0; i < MAX_PARTICLES; i++) {
			if (particles[i].status == 0) {
				particles[i].point.xPos = generateInt(emissionXMin, emissionXMax);
				particles[i].point.yPos = generateInt(emissionYMin, emissionYMax);
				particles[i].point.zPos = generateInt(emissionZMin, emissionZMax);
				particles[i].velocity = generateFloat(0.1, 0.2);
				particles[i].color[0] = 265.0;
				particles[i].color[1] = 165.0;
				particles[i].color[2] = 0.0;
				particles[i].temperature = 100.0;	
				particles[i].age = 0;
				particles[i].lifespan = generateInt(0, 80);
				particles[i].id = i;
				particles[i].status = 1;
				break;
			}
		}
		// Modify particles as necessary
		for (i = 0; i < MAX_PARTICLES; i++) {
			if (particles[i].status == 1) {
				// X Movement
				if (generateInt(0, 2) == 0) {
					particles[i].point.xPos += particles[i].velocity;
				}
				else {
					particles[i].point.xPos -= particles[i].velocity;
				}
				// Z Movement
				if (generateInt(0, 2) == 0) {
					particles[i].point.zPos += particles[i].velocity;
				}
				else {
					particles[i].point.zPos -= particles[i].velocity;
				}
				// Y Movement
				particles[i].point.yPos += particles[i].velocity;
				// Lower lifespan
				particles[i].lifespan--;
				// Kill particle if lifespan ends
				if (particles[i].lifespan < 0) {
					particles[i].status = 2;
				}
			}
		}
		// Delete old particles
		for (i = 0; i < MAX_PARTICLES; i++) {
			if (particles[i].status == 2) {
				particles[i].status = 0;
			}
		}
	}

	void drawScene() {
		int i = 0;
		glPointSize(5);
		glBegin(GL_POINTS);
		for (i = 0; i < MAX_PARTICLES; i++) {
			if (particles[i].status == 1) {
				glColor3f(particles[i].color[0], particles[i].color[1], particles[i].color[2]);
				glVertex3f(particles[i].point.xPos, particles[i].point.yPos, particles[i].point.zPos);
			}
		}
		glEnd();
	}

};