#include "structs.h"
#include <math.h> 

#define SIN(x) sin(x * 3.14159265358979323846/180) 
#define COS(x) cos(x * 3.14159265358979323846/180)  

struct Point* checkForPoint(struct Polygon polygons[], int currentPolygons, int x, int y) {
	int i;
	int j;
	for (i = 0; i < currentPolygons; i++) {
		for (j = 0; j < polygons[i].numPoints; j++) {
			if ((polygons[i].vertices[j].x >= x-3 && 
				polygons[i].vertices[j].x <= x+3) &&
				(polygons[i].vertices[j].y >= y-3 && 
				polygons[i].vertices[j].y <= y+3)) {
					return &polygons[i].vertices[j];
			}
		}
	}
	return 0;
}

struct Polygon* checkForPolygon(struct Polygon polygons[], int currentPolygons, struct Point* selectedPoint) {
	int i;
	int j;
	for (i = 0; i < currentPolygons; i++) {
		for (j = 0; j < polygons[i].numPoints; j++) {
			if (selectedPoint == &polygons[i].vertices[j]) {
				return &polygons[i];
			}
		}
	}
	return 0;
}

void translation(struct Polygon* polygon, int x, int y) {
	int i;
	for (i = 0; i < polygon->numPoints; i++) {
		polygon->vertices[i].x += x;
		polygon->vertices[i].y += y;
	}
}

void scale(struct Polygon* polygon, int x, int y) {
	int i;
	for (i = 0; i < polygon->numPoints; i++) {
		polygon->vertices[i].x *= x;
		polygon->vertices[i].y *= y;
	}
}

void rotation(struct Polygon* polygon, int angle) {
	int i;
	int temp;
	for (i = 0; i < polygon->numPoints; i++) {
		temp = polygon->vertices[i].x;
		polygon->vertices[i].x = polygon->vertices[i].x * COS(angle) - polygon->vertices[i].y * SIN(angle);
		polygon->vertices[i].y = temp * SIN(angle) + polygon->vertices[i].y * COS(angle);
	}
}

void shear(struct Polygon* polygon, int x, int y) {
	int i;
	int temp;
	for (i = 0; i < polygon->numPoints; i++) {
		temp = polygon->vertices[i].x;
		polygon->vertices[i].x += x * polygon->vertices[i].y;
		polygon->vertices[i].y += y * temp;
	}
}

void reflection(struct Polygon* polygon) {
	int i;
	int temp;
	for (i = 0; i < polygon->numPoints; i++) {
		temp = polygon->vertices[i].x;
		polygon->vertices[i].x = -polygon->vertices[i].y;
		polygon->vertices[i].y = -temp;
	}
}