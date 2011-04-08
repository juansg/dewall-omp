/* Data structures */
#include <limits.h>

#define EPSILON 0.000001
#define MAX_RADIUS INT_MAX

typedef struct {   
  float x, y;
} point;

typedef struct {
  point *base_point;
  point **point;  
  int size;
} point_set;


typedef struct {
  point normal;
  float off;
} plane;

typedef struct {	
  point *point[2];			
} face; 

typedef int Axis;
enum Axis {XAxis, YAxis};

/* Geometry  */
int compare_points_X(const void *p1, const void *p2);
int compare_points_Y(const void *p1, const void *p2);

float distance(point *a, point *b);
float circumCircleRadius(point *a, point *b, point *c);
int circumCircleCentre(point *a, point *b, point *c, point *centre);
int circumCircleCentreAndRadius(point *a, point *b, point *c, point *centre, float *r);

int right_side(point *p, plane *alpha);
int intersect(face *f, plane *alpha);
Axis invert_axis(Axis ax);

int pointLocationRelativeToFace(face *face, point *p);
