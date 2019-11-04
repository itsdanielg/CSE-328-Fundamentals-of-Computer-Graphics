#include "point.cpp"

class Particle {

	public:

	int status;				// 0 = N/A, 1 = LIVE, 2 = DEAD
	Point point;
	float velocity;
	float color[3];
	float temperature;
	float age;
	float lifespan;
	int id;

};