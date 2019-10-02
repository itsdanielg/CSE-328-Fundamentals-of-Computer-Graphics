#define MAX_POINTS 30
#define MAX_POLYGONS 10

struct Point {
	int x;
	int y;
};

struct Line {
	struct Point* a;
	struct Point* b;
};

struct Polygon {
	int numPoints;
	int numLines;
	char complete;
	char isSimple;
	struct Point vertices[MAX_POINTS];
	struct Line lines[MAX_POINTS];
};
