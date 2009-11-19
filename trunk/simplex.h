#include <stdio.h>
#include <stdlib.h>

/* Data structures */

typedef struct {   
	float x, y;
} point;

typedef struct {
    point* point;
    int size;
} point_set;

    
typedef struct {
    point normal;
    float off;
} plane;

typedef struct {	
    point point[2];			
} face;   
    
//TODO: create real face list 
typedef face* face_list;    

typedef struct {
    face face[3];
} simplex;

//TODO: create real simplex list
typedef simplex* simplex_list;

typedef int Axis;

enum Axis {XAxis, YAxis};

/* IO */

int read_points(char *filename, point_set *P);
void print_points (FILE *fp, point_set *P);
int write_simplex_list(char *filename, simplex_list *s);

/* Face list handling */
int insert_simplex(simplex *t, simplex_list *E);
int insert_list(face *f, face_list *AFLa);
int extract_list(face *f, face_list *AFL);
int make_simplex(face *f, point_set *P, simplex *s);
int update_face(face *f1, face_list *AFLa);
void initialize_face_list(face_list *AFL);
void initialize_plane(point_set *P, plane* alpha, Axis ax);

/* Geometry  */
int compare_points_X(const void *p1, const void *p2);
int compare_points_Y(const void *p1, const void *p2);
int intersect(face *f, plane *alpha);
Axis invert_axis(Axis ax);
float distance(point a, point b);
float circumCircleRadius(point a, point b, point c);
