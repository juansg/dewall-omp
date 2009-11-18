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

/* Functions */

int read_points(char *filename, point_set *P);
void print_points (FILE *fp, point_set *P);
int write_simplex_list(char *filename, simplex_list *s);

/* Functions not implemented yet!!!*/

int pointset_partition(point_set *P, plane *alpha, point_set *P1, point_set *P2);

int make_first_simplex(point_set *P, plane *alpha, simplex *s);

int insert_simplex(simplex *t, simplex_list *E);

int intersect(face *f, plane *alpha);

int insert_list(face *f, face_list *AFLa);

int extract_list(face *f, face_list *AFL);

int make_simplex(face *f, point_set *P, simplex *s);

int update_face(face *f1, face_list *AFLa);

void initialize_face_list(face_list *AFL);

void initialize_plane(point_set *P, plane* alpha, Axis ax);

Axis invertAxis(Axis ax);
