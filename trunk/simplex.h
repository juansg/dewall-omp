#include "geometry.h" 
#include "hashlist.h" 
#include <stdio.h>
    
typedef list face_list;    

typedef struct {
    face *face[3];
} simplex;

typedef list simplex_list;

/* IO */
int read_points(char *filename, point_set *P);
void print_points (FILE *fp, point_set *P);
int write_simplex_list(char *filename, simplex_list *sl);

/* Face list handling */
int build_simplex(simplex **s, face *f, point *p);
int insert_simplex(simplex *t, simplex_list *E);

int insert_face(face *f, face_list *AFLa);
int extract_face(face **f, face_list *AFL);
int update_face(face *f1, face_list *AFLa);
void initialize_face_list(face_list *AFL, int size);
void revert_face(face *f);
