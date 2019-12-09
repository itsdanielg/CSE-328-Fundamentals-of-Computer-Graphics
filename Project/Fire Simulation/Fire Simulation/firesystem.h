#pragma once

#ifndef FIRESYSTEM_H
#define FIRESYSTEM_H

#include "particlesystem.h"
#include "particle.h"

class FireSystem : public ParticleSystem {

public:

	void changeColor(Particle* particle);
	void calculateTurbulence(Particle* particle, int deltaTime);
	void createParticles();
	void modifyParticles(int deltaTime);
	void step(int deltaTime);

};

#endif;