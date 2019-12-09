#pragma once

#ifndef PARTICLE_H
#define PARTICLE_H

#include "point.h"

class Particle {

public:

	char status;				// 0 = DEAD, 1 = LIVE
	Point point;
	float velocity;
	float noiseX;
	float noiseY;
	float red;
	float green;
	float blue;
	float alpha;
	float temperature;
	float age;
	float lifespan;
	int id;

};

#endif