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

int compare_points_X(const void *vp1, const void *vp2) {
	point *p1 = (point *) vp1;
	point *p2 = (point *) vp2;
	if (p1->x > p2->x)
		return 1;
	else if (p1->x < p2->x)
		return -1;
	else
		return 0;
}

int compare_points_Y(const void *vp1, const void *vp2) {
	point *p1 = (point *) vp1;
	point *p2 = (point *) vp2;
	if (p1->y > p2->y)
		return 1;
	else if (p1->y < p2->y)
		return -1;
	else
		return 0;
}

int intersect(face *f, plane *alpha) {
	return 0;
}

Axis invert_axis(Axis ax) {
	return !ax;
}

float distance(point *a, point *b) {
	return sqrtf(powf(a->x - b->x, 2) + powf(a->y - b->y, 2));
}

float circumCircleRadius(point *a, point *b, point *c) {
	float deltaAB = powf(a->x - b->x, 2) + powf(a->y - b->y, 2);
	float deltaBC = powf(b->x - c->x, 2) + powf(b->y - c->y, 2);
	float deltaAC = powf(a->x - c->x, 2) + powf(a->y - c->y, 2);

	float dividend = sqrtf(deltaAB) * sqrtf(deltaBC) * sqrtf(deltaAC);
	float divisor = 2 * (b->x * a->y - c->x * a->y - a->x * b->y + c->x * b->y
			+ a->x * c->y - b->x * c->y);
	if ((dividend || divisor) == 0)
		return 0;
	return fabsf(dividend / divisor);
}
