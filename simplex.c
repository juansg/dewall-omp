#include "simplex.h"
#include <math.h>

#define EPSILON 0.000001

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
	if (dividend == 0 || divisor == 0)
		return 0;
	return fabsf(dividend / divisor);
}

point* circumCircleCentre(point *a, point *b, point*c) {
	float m1, m2, mx1, mx2, my1, my2;
	float xc, yc;
	point *centre = (point *) malloc(sizeof(point));

	// Check for coincident points
	if (fabsf(a->y - b->y) < EPSILON && fabsf(b->y - c->y) < EPSILON)
		return;

	if (fabsf(b->y - a->y) < EPSILON) {
		m2 = -(c->x - b->x) / (c->y - b->y);
		mx2 = (b->x + c->x) / 2.0;
		my2 = (b->y + c->y) / 2.0;
		xc = (b->x + a->x) / 2.0;
		yc = m2 * (xc - mx2) + my2;
	} else if (fabsf(c->y - b->y) < EPSILON) {
		m1 = -(b->x - a->x) / (b->y - a->y);
		mx1 = (a->x + b->x) / 2.0;
		my1 = (a->y + b->y) / 2.0;
		xc = (c->x + b->x) / 2.0;
		yc = m1 * (xc - mx1) + my1;
	} else {
		m1 = -(b->x - a->x) / (b->y - a->y);
		m2 = -(c->x - b->x) / (c->y - b->y);
		mx1 = (a->x + b->x) / 2.0;
		mx2 = (b->x + c->x) / 2.0;
		my1 = (a->y + b->y) / 2.0;
		my2 = (b->y + c->y) / 2.0;
		xc = (m1 * mx1 - m2 * mx2 + my2 - my1) / (m1 - m2);
		yc = m1 * (xc - mx1) + my1;
	}

	centre->x = xc;
	centre->y = yc;

	return centre;
}
