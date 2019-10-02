int max(int a, int b);
int min(int a, int b);
char onLine(struct Point* p1, struct Point* p2, struct Point* p3);
int checkOrientation(struct Point* p1, struct Point* p2, struct Point* p3);
char isIntersecting(struct Point* a1, struct Point* b1, struct Point* a2, struct Point* b2);
int checkIntersections(struct Polygon* polygon);
void resetPolygon(struct Polygon* polygon);
int removeNonSimple(struct Polygon polygons[]);
void rearrangeArr(struct Polygon polygons[], int currentPolygons);