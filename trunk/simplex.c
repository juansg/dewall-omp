#include "simplex.h"

/* face list functions */
int insert_simplex(simplex *t, simplex_list *E){return 0;}

int insert_list(face *f, face_list *AFLa){return 0;}

int extract_list(face *f, face_list *AFL){return 0;}

int update_face(face *f1, face_list *AFLa){return 0;}

void initialize_face_list(face_list *AFL){*AFL == NULL;}

/* geometry functions */
int intersect(face *f, plane *alpha){return 0;}

Axis invertAxis(Axis ax){
   return !ax;
}
