#include "math.h"

class Point {

	public:

	float xPos;
	float yPos;
	float zPos;

	void add(Point point) {
		this->xPos += point.xPos;
		this->yPos += point.yPos;
		this->zPos += point.zPos;
	}

	void subract(Point point) {
		this->xPos -= point.xPos;
		this->yPos -= point.yPos;
		this->zPos -= point.zPos;
	}

	void multiply(Point point) {
		this->xPos *= point.xPos;
		this->yPos *= point.yPos;
		this->zPos *= point.zPos;
	}

	void divide(Point point) {
		this->xPos /= point.xPos;
		this->yPos /= point.yPos;
		this->zPos /= point.zPos;
	}

};