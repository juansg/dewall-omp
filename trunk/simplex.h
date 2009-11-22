#include "geometry.h" 
#include "hashlist.h" 
#include <stdio.h>
    
//TODO: create real face list 
typedef face* face_list;    

typedef struct {
    face face[3];
} simplex;

//TODO: create real simplex list
typedef simplex* simplex_list;

/* IO */

int read_points(char *filename, point_set *P);
void print_points (FILE *fp, point_set *P);
int write_simplex_list(char *filename, simplex_list *s);

/* Face list handling */
int insert_simplex(simplex *t, simplex_list *E);
int insert_face(face *f, face_list *AFLa);
int extract_face(face *f, face_list *AFL);
int update_face(face *f1, face_list *AFLa);
void initialize_face_list(face_list *AFL);
