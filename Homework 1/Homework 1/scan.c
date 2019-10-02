#include "structs.h"
#include <string.h>

// Helper function to find the max value between two integers
int max(int a, int b) { 
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
} 
  
// Helper function to find the min value between two integers
int min(int a, int b) { 
	if (a > b) {
		return b;
	}
	else {
		return a;
	}
}

// Function to check if p2 lies on line segment (p1, p3)
char onLine(struct Point p1, struct Point p2, struct Point p3) {
	int x1 = p1.x;
	int x2 = p2.x;
	int x3 = p3.x;
	int y1 = p1.y;
	int y2 = p2.y;
	int y3 = p3.y;
	if (x2 <= max(x1, x3) && x2 >= min(x1, x3) && y2 <= max(y1, y3) && y2 >= min(y1, y3)) {
		return 1;
	}
	return -1;
}

// Function to check the orientation between three given points
int checkOrientation(struct Point p1, struct Point p2, struct Point p3) {
	int x1 = p1.x;
	int x2 = p2.x;
	int x3 = p3.x;
	int y1 = p1.y;
	int y2 = p2.y;
	int y3 = p3.y;
	int checkVal = (y2 - y1) * (x3 - x2) - (x2 - x1) * (y3 - y2);
	// Returns if points are collinear, clockwise, or counter-clockwise respectively
	if (checkVal == 0) return 0;
	else if (checkVal > 0) return 1;
	return 2;
}

// Function to check if two line segments intersect
char isIntersecting(struct Point a1, struct Point b1, struct Point a2, struct Point b2) {
	int oriOne = checkOrientation(a1, b1, a2);
	int oriTwo = checkOrientation(a1, b1, b2);
	int oriThree = checkOrientation(a2, b2, a1);
	int oriFour = checkOrientation(a2, b2, b1);

	// Do not count line segments with the same vertex
	if ((a1.x == a2.x && a1.y == a2.y) || 
		(a1.x == b2.x && a1.y == b2.y) ||
		(b1.x == a2.x && b1.y == a2.y) ||
		(b1.x == b2.x && b1.y == b2.y)) {
			return -1;
	}

	if (oriOne != oriTwo && oriThree != oriFour) return 1;

	if (oriOne == 0 && onLine(a1, a2, b1)) return 1;
	if (oriTwo == 0 && onLine(a1, b2, b1)) return 1;
	if (oriThree == 0 && onLine(a2, a1, b2)) return 1;
	if (oriFour == 0 && onLine(a2, b1, b2)) return 1;

	return -1;
}

// Function to check if intersections exist within the polygon
int checkIntersections(struct Polygon* polygon) {
	int i;
	int j;
	struct Point a1;
	struct Point b1;
	struct Point a2;
	struct Point b2;
	if (polygon->numPoints < 3) return -1;
	for (i = 0; i < polygon->numLines - 1; i++) {
		for (j = i + 1; j < polygon->numLines; j++) {
			a1 = polygon->lines[i].a;
			b1 = polygon->lines[i].b;
			a2 = polygon->lines[j].a;
			b2 = polygon->lines[j].b;
			if (isIntersecting(a1, b1, a2, b2) == 1) {
				polygon->isSimple = -1;
				return 1;
			}
		}
	}
	return -1;
}

void resetPolygon(struct Polygon* polygon) {
	polygon->numPoints = 0;
	polygon->numLines = 0;
	polygon->complete = 0;
	polygon->isSimple = 0;
	memset(polygon->vertices, 0, sizeof(polygon->vertices));
	memset(polygon->lines, 0, sizeof(polygon->lines));
}

int removeNonSimple(struct Polygon polygons[]) {
	int i;
	int removed = 0;
	for (i = 0; i < MAX_POLYGONS; i++) {
		if (polygons[i].complete == 1) {
			if (polygons[i].isSimple != 1) {
				resetPolygon(&polygons[i]);
				removed++;
			}
		}
	}
	return removed;
}

void rearrangeArr(struct Polygon polygons[], int currentPolygons) {
	int index;
	int i = 0;
	int j = 0;
	for (i = 0; i < MAX_POLYGONS; i++) {
		if (j == currentPolygons) break;
		// Check if this index contains a polygon
		if (polygons[i].numPoints > 0) {
			if (polygons[j].numPoints == 0) {
				polygons[j].numPoints = polygons[i].numPoints;
				polygons[j].numLines = polygons[i].numLines;
				polygons[j].complete = polygons[i].complete;
				polygons[j].isSimple = polygons[i].isSimple;
				for (index = 0; index < MAX_POINTS; index++) {
					polygons[j].vertices[index].x = polygons[i].vertices[index].x;
					polygons[j].vertices[index].y = polygons[i].vertices[index].y;
					polygons[j].lines[index].a.x = polygons[i].lines[index].a.x;
					polygons[j].lines[index].a.y = polygons[i].lines[index].a.y;
					polygons[j].lines[index].b.x = polygons[i].lines[index].b.x;
					polygons[j].lines[index].b.y = polygons[i].lines[index].b.y;
				}
				resetPolygon(&polygons[i]);
			}
			j++;
		}
	}
}