#include "simplex.h"


/* Functions not implemented yet!!!*/

int pointset_partition(point_set *P, plane *alpha, point_set *P1, point_set *P2){return 0;}

int make_first_simplex(point_set *P, plane *alpha, simplex *s){return 0;}

int insert_simplex(simplex *t, simplex_list *E){return 0;}

int intersect(face *f, plane *alpha){return 0;}

int insert_list(face *f, face_list *AFLa){return 0;}

int extract_list(face *f, face_list *AFL){return 0;}

int make_simplex(face *f, point_set *P, simplex *s){return 0;}

int update_face(face *f1, face_list *AFLa){return 0;}

void initialize_face_list(face_list *AFL){*AFL == NULL;}

void initialize_plane(point_set *P, plane* alpha, Axis ax){}

Axis invertAxis(Axis ax){
   return !ax;
}
