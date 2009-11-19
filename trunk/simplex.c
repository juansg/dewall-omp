#include "simplex.h"
#include <math.h>

/* Functions not implemented yet!!! */

/* face list handling */
int insert_simplex(simplex *t, simplex_list *E) {
	return 0;
}
int insert_list(face *f, face_list *AFLa) {
	return 0;
}
int extract_list(face *f, face_list *AFL) {
	return 0;
}
int update_face(face *f1, face_list *AFLa) {
	return 0;
}
void initialize_face_list(face_list *AFL) {
	*AFL = NULL;
}

/* geometry */
int intersect(face *f, plane *alpha) {
	return 0;
}

Axis invertAxis(Axis ax) {
	return !ax;
}

float distance(point a, point b) {
	return sqrtf(powf(a.x - b.x, 2) + powf(a.y - b.y, 2));
}

float circumCircleRadius(point a, point b, point c) {
	float deltaAB = powf(a.x - b.x, 2) + powf(a.y - b.y, 2);
	float deltaBC = powf(b.x - c.x, 2) + powf(b.y - c.y, 2);
	float deltaAC = powf(a.x - c.x, 2) + powf(a.y - c.y, 2);

	float dividend = sqrtf(deltaAB) * sqrtf(deltaBC) * sqrtf(deltaAC);
	float divisor = 2 * (b.x * a.y - c.x * a.y - a.x * b.y + c.x * b.y + a.x * c.y
			- b.x * c.y);
	return abs(dividend/divisor);
}
