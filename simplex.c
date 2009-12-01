#include "simplex.h"
#include <stdlib.h>

/* face list handling */

int equal_face(void *vf1, void *vf2)  {
  	face *f1 = (face *) vf1;
	face *f2 = (face *) vf2;  
    
    if (f1->point[0] != f2->point[0] && 
		f1->point[0] != f2->point[1])
		return 0;
		
	if (f1->point[1] != f2->point[0] && 
		f1->point[1] != f2->point[1])
		return 0;
	
	return 1;
}

int hash_face(void *vf) {
  face *f = (face *) vf;
  return (int)((long)(f->point[0]) ^ (long)(f->point[1]));
}

int insert_face(face *f, face_list *AFL) {
	return insert_list(AFL, f);
}
int extract_face(face **f, face_list *AFL) {
	return extract_list(AFL, f);
}
int update_face(face *f, face_list *AFL) {
	if (member_list(AFL, f)){
		delete_list(AFL, f);     
   }
	else 
		insert_list(AFL, f);
}
void initialize_face_list(face_list *AFL, int size) {
	initialize_list(AFL,sizeof(face *),equal_face);
    hash_list(AFL, size, hash_face);
}

/* simplex list handling */

int hash_simplex(void *vs) {
  simplex *s = (simplex *) vs;
  return (hash_face(&(s->face[0])) ^ hash_face(&(s->face[1])) ^ 
		hash_face(&(s->face[2])));
}

void initialize_simplex_list(simplex_list *sl, int size) {
	initialize_list(sl,sizeof(char *),NULL);
}

int insert_simplex(simplex *s, simplex_list *sl, point_set *P) {	
   // Deallocated in write_simplex_list
   simplex_index *simp = (simplex_index *)malloc(sizeof(simplex_index));
   
   simp->index[0] = s->face[0]->point[0] - P->base_point;
   simp->index[1] = s->face[0]->point[1] - P->base_point;

   if ((s->face[1]->point[0] - P->base_point) != simp->index[0] && 
         (s->face[1]->point[0] - P->base_point) != simp->index[1])
      simp->index[2] = s->face[1]->point[0] - P->base_point;
   else 
      simp->index[2] = s->face[1]->point[1] - P->base_point;

   // Alocated in build_simplex function   
   free(s);
   return insert_list(sl, simp);
}

int extract_simplex(simplex_index **s, simplex_list *sl) {
	return extract_list(sl, s);   
}

int build_simplex(simplex **s, face *f, point *p) {
   // Deallocated in insert_simplex function 
	*s = (simplex *)malloc(sizeof(simplex));
	
	if (!(*s))
		return 0;
		
	(*s)->face[0] = (*s)->face[1] = (*s)->face[2] = NULL;
	
   // Deallocated in dewall function
	(*s)->face[0] = (face *)malloc(sizeof(face));
	(*s)->face[1] = (face *)malloc(sizeof(face));
	(*s)->face[2] = (face *)malloc(sizeof(face));

	if(!((*s)->face[0] && (*s)->face[1] && (*s)->face[2]))
		return 0;

	(*s)->face[0]->point[0] = f->point[0];
	(*s)->face[0]->point[1] = f->point[1];

	(*s)->face[1]->point[0] = f->point[0];
	(*s)->face[1]->point[1] = p;
 
	(*s)->face[2]->point[0] = p;
	(*s)->face[2]->point[1] = f->point[1];	
	
	printf("simplex: (%.3f, %.3f)(%.3f, %.3f)(%.3f, %.3f)\n",
            (*s)->face[0]->point[0]->x, (*s)->face[0]->point[0]->y,
            (*s)->face[0]->point[1]->x, (*s)->face[0]->point[1]->y,
            (*s)->face[1]->point[1]->x, (*s)->face[1]->point[1]->y);
	return 1;
}

void revert_face(face *f){
   point *p;
   p = f->point[0];
   f->point[0] = f->point[1];
   f->point[1] = p;   
}
