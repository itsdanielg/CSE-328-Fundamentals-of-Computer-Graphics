#include "particlesystem.h"
#include "particle.h"
#include "firesystem.h"
#include "globalvar.h"
#include "noise.h"

float flameR = 245.0;
float flameG = 255.0;
float flameB = 10.0;

void FireSystem::changeColor(Particle* particle) {
	particle->red = flameR/255.0;
	particle->green = (1 - particle->point.yPos/5.0);
	particle->blue = flameB/255.0;
	particle->alpha = (particle->temperature/100.0);
}

void FireSystem::calculateTurbulence(Particle* particle, int deltaTime) {
	int amplitude = 0.99 + fireTurbulenceAmp;
	int frequency = 0.99 + fireTurbulenceScale;
	particle->noiseX += 0.01;
	float one = (amplitude * 2.2) * pn.computeNoise(particle->noiseX * (frequency * 0.7));
	float two = (amplitude) * pn.computeNoise(particle->noiseX * (frequency));
	float three = (amplitude * 0.4) * pn.computeNoise(particle->noiseX * (frequency * 3.1));
	float noise = one + two + three;
	float multiplier = 1/particle->temperature * deltaTime;
	noise *= multiplier;
	particle->point.xPos += noise;
	particle->point.zPos += noise;
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
			particles[i].point.xPos = generateFloat(emissionXMin, emissionXMax);
			particles[i].point.yPos = generateFloat(emissionYMin, emissionYMax);
			particles[i].point.zPos = generateFloat(emissionZMin, emissionZMax);
			particles[i].velocity = generateFloat(minVel, maxVel);
			particles[i].noiseX = generateFloat(0, 1);
			particles[i].noiseY = generateFloat(0, 1);
			// FLAME COLOR
			particles[i].red = flameR/255.0;
			particles[i].green = flameG/255.0;
			particles[i].blue = flameB/255.0;
			particles[i].alpha = 1.0;
			particles[i].temperature = maxTemp;	
			particles[i].age = 0;
			particles[i].lifespan = 100 * (int) (pn.computeNoise(0.15) + 1.0) / 2.0;
			particles[i].id = id;
			particles[i].status = 1;
			break;
		}
	}
}

void FireSystem::modifyParticles(int deltaTime) {
	int i = 0;
	for (i = 0; i < MAX_PARTICLES; i++) {
		if (particles[i].status == 1) {
			// Update age
			particles[i].age++;
			// Lower temperature
			particles[i].temperature -= fireCoolRate;
			// Change color based on temperature
			changeColor(&particles[i]);
			// X Movement based on temperature
			particles[i].point.xPos += (fireWindX * 1/particles[i].temperature * deltaTime);
			// Z Movement based on temperature
			particles[i].point.zPos += (fireWindZ * 1/particles[i].temperature * deltaTime);
			// Y Movement based on temperature
			particles[i].point.yPos += (fireWindY * 1/particles[i].temperature * deltaTime);
			particles[i].point.yPos += (particles[i].velocity * fireRiseRate * particles[i].temperature * deltaTime);
			// Calculate Turbulence
			calculateTurbulence(&particles[i], deltaTime);
			// Kill particle if lifespan ends
			if (particles[i].age >= particles[i].lifespan) {
				particles[i].status = 0;
			}
		}
	}
}

void FireSystem::step(int deltaTime) {
	// Create new particle
	int i;
	for (i = 0; i < emitterRate; i++) {
		createParticles();
	}
	// Modify particles as necessary
	modifyParticles(deltaTime);
}