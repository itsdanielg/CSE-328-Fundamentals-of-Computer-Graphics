struct Point* checkForPoint(struct Polygon polygons[], int currentPolygons, int x, int y);
struct Polygon* checkForPolygon(struct Polygon polygons[], int currentPolygons, struct Point* selectedPoint);
void translation(struct Polygon* polygon, int x, int y);
void scale(struct Polygon* polygon, int x, int y);
void rotation(struct Polygon* polygon, int angle);
void shear(struct Polygon* polygon, int x, int y);
void reflection(struct Polygon* polygon);