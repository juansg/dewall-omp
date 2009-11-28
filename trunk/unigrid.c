#include "geometry.h"
#include <math.h>

typedef struct {
	point *p;
	cell *next;
} cell;

float xMin(point_set *P);
float xMax(point_set *P);
float yMin(point_set *P)
float yMax(point_set *P);
float gridSize(float xmin, float xmax, float ymin, float ymax, int size);
int xRes(float gridSize, float xmin, float xmax);
int yRes(float gridSize, float ymin, float ymax);

float xMin(point_set *P) {
	float xmin = P->base_point[0];
	int i;
	for (i = 1; i < P->size; i++) {
		if (P->base_point[i] < xmin)
			xmin = P->base_point[i];
	}
	return xmin - EPSILON;
}

float xMax(point_set *P) {
	float xmax = P->base_point[0];
	int i;
	for (i = 1; i < P->size; i++) {
		if (P->base_point[i] > xmax)
			xmax = P->base_point[i];
	}
	return xmax + EPSILON;
}

float yMin(point_set *P) {
	float ymin = P->base_point[0];
	int i;
	for (i = 1; i < P->size; i++) {
		if (P->base_point[i] < ymin)
			ymin = P->base_point[i];
	}
	return ymin - EPSILON;
}

float yMax(point_set *P) {
	float ymax = P->base_point[0];
	int i;
	for (i = 1; i < P->size; i++) {
		if (P->base_point[i] > ymax)
			ymax = P->base_point[i];
	}
	return ymax + EPSILON;
}

float gridSize(float xmin, float xmax, float ymin, float ymax, int size) {
	float gridSize;
	gridSize = sqrt((((xmax - xmin) * (ymax - ymin)) / size));
	return gridSize;
}

int xRes(float gridSize, float xmin, float xmax) {
	int xRes;
	xRes = (int) truncf((xmax - xmin) / gridSize) + 1;
}

int yRes(float gridSize, float ymin, float ymax) {
	int yRes;
	yRes = (int) truncf((ymax - ymin) / gridSize) + 1;
}

cell* createUniformGrid(point_set *P) {
	float xmin = xMin(P), xmax = xMax(P), ymin = yMin(P), ymax = yMax(P);
	float gridsize = gridSize(xmin, xmax, ymin, ymax, P->size);
	cell *uniformGrid[xRes(gridsize, xmin, xmax)][yRes(gridsize, ymin, ymax)];
	int i;
	for (i = 0; i < P->size; i++) {
		cell *c = (cell *) malloc(sizeof cell);
		int xGrid = (int) truncf(((P->base_point[i].x - xmin) / gridsize));
		int yGrid = (int) truncf(((P->base_point[i].y - ymin) / gridsize));
		if (uniformGrid[xGrid][yGrid] == null) {
			uniformGrid[xGrid][yGrid] = c;
			c->p = P->point_base->x;
			c->next = NULL;
		} else {
			while (uniformGrid[xGrid][yGrid]->next != null) {
				c = uniformGrid[xGrid][yGrid]->next;
			}
			c->p = P->point_base->x;
			c->next = NULL;
		}
	}
	return uniformGrid;
}

