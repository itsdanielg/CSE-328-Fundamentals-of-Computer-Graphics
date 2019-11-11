#pragma once

#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "particle.h"

#define MAX_PARTICLES 5000

class ParticleSystem {

public:

	int id;
	Particle particles[MAX_PARTICLES];
	int generateInt(int min, int max);
	float generateFloat(float min, float max);
	void resetSystem();
	void createParticles();
	void modifyParticles();
	void step();
	void drawScene();

};

#endif