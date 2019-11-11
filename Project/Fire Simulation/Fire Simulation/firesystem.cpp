#include "particlesystem.h"
#include "particle.h"
#include "firesystem.h"
#include "globalvar.h"

void FireSystem::changeColor(Particle* particle) {
	particle->red = 245.0/255.0;
	particle->green = (particle->temperature/100*152.0)/255.0;
	particle->blue = (particle->temperature/100*29.0)/255.0;
}

void FireSystem::calculateTurbulence(Particle* particle) {
	// X Movement
	if (generateInt(0, 2) == 0) {
		particle->point.xPosOne += fireTurbulenceAmp;
		particle->point.xPosTwo += fireTurbulenceAmp;
	}
	else {
		particle->point.xPosOne -= fireTurbulenceAmp;
		particle->point.xPosTwo -= fireTurbulenceAmp;
	}
	// Z Movement
	if (generateInt(0, 2) == 0) {
		particle->point.zPosOne += fireTurbulenceAmp;
		particle->point.zPosTwo += fireTurbulenceAmp;
	}
	else {
		particle->point.zPosOne -= fireTurbulenceAmp;
		particle->point.zPosTwo -= fireTurbulenceAmp;
	}
}

void FireSystem::createParticles() {
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
			particles[i].velocity = generateFloat(minVel, maxVel);
			particles[i].point.xPosOne = generateInt(emissionXMin, emissionXMax);
			particles[i].point.yPosOne = generateInt(emissionYMin, emissionYMax);
			particles[i].point.zPosOne = generateInt(emissionZMin, emissionZMax);
			particles[i].point.xPosTwo = particles[i].point.xPosOne + 0.1;
			particles[i].point.yPosTwo = particles[i].point.yPosOne;
			particles[i].point.zPosTwo = particles[i].point.zPosOne;
			// FLAME COLOR
			particles[i].red = 245.0/255.0;
			particles[i].green = 208.0/255.0;
			particles[i].blue = 32.0/255.0;
			particles[i].temperature = maxTemp;	
			particles[i].age = 0;
			particles[i].lifespan = generateInt(0, maxLifespan);
			particles[i].id = id;
			particles[i].status = 1;
			break;
		}
	}
}

void FireSystem::modifyParticles() {
	int i = 0;
	for (i = 0; i < MAX_PARTICLES; i++) {
		if (particles[i].status == 1) {
			// X Movement
			particles[i].point.xPosOne += fireWindX;
			particles[i].point.xPosTwo += fireWindX;
			// Z Movement
			particles[i].point.zPosOne += fireWindZ;
			particles[i].point.zPosTwo += fireWindZ;
			// Y Movement
			particles[i].point.yPosOne += particles[i].velocity * fireRiseRate + fireWindY;
			particles[i].point.yPosTwo += particles[i].velocity * fireRiseRate + fireWindY;
			// Calculate Turbulence
			calculateTurbulence(&particles[i]);
			// Lower lifespan
			particles[i].lifespan--;
			particles[i].age++;
			// Lower temperature
			particles[i].temperature -= fireCoolRate;
			// Change color based on temperature
			changeColor(&particles[i]);
			// Kill particle if lifespan ends
			if (particles[i].lifespan < 0) {
				particles[i].status = 0;
			}
		}
	}
}

void FireSystem::step() {
	// Create new particle
	int i;
	for (i = 0; i < emitterRate; i++) {
		createParticles();
	}
	// Modify particles as necessary
	modifyParticles();
}