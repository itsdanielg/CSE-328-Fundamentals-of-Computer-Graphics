#include "structs.h"

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