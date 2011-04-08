#include "geometry.h" 
#include "hashlist.h" 
#include <stdio.h>

typedef list face_list;    

typedef struct {
  face *face[3];
} simplex;

typedef struct {
  int index[3];
} simplex_index;

typedef list simplex_list;

/* IO */
int read_points(char *filename, point_set *P);
void print_points (FILE *fp, point_set *P);
int write_simplex_list(char *filename, simplex_list *sl, point_set *P);

/* Face list handling */
void initialize_simplex_list(simplex_list *sl, int size);
int build_simplex(simplex **s, face *f, point *p);
int insert_simplex(simplex *s, simplex_list *sl, point_set *P);
int extract_simplex(simplex_index **s, simplex_list *sl);
int equal_simplex(void *vs1, void *vs2) ;

int insert_face(face *f, face_list *AFLa);
int extract_face(face **f, face_list *AFL);
int update_face(face *f1, face_list *AFLa);
void initialize_face_list(face_list *AFL, int size);
void revert_face(face *f);
