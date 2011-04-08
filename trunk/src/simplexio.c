#include <stdio.h>
#include <stdlib.h>
#include "simplex.h"

//Debug trick
#define LOGGER printf("[%s - %s] : file %s, line %d\n", __DATE__, __TIME__, __FILE__,__LINE__)


int read_points(char *filename, point_set *P) {
  FILE *fp;
  int i = -1, j;
  point p;

  fp=fopen(filename,"r");
  if(fp) {
    fscanf(fp,"%d",&(P->size));
    // Not deallocated: created once and always needed during the algorithm's execution
    P->base_point = (point *)malloc(sizeof(point)*P->size);
    P->point = (point **)malloc(sizeof(point *)*P->size);
    if(P->point)
      for(i = 0; i < P->size; i++) {
        fscanf(fp,"%f %f",&(P->base_point[i].x),&(P->base_point[i].y));
#ifdef DEBUG
        printf("%f %f\n",P->base_point[i].x, P->base_point[i].y);
#endif
      }

    // Create vector of pointers
    for (j = 0; j < P->size; j++){
      P->point[j] = &(P->base_point[j]);
    }
  }
  return i;
}

int write_points(char *filename, point_set *P) {
  FILE *fp = fopen(filename,"w");
  if (!fp)
    return 0;
  print_points(fp, P);  
  fclose(fp);    
  return 1;
}

void print_points (FILE *fp, point_set *P) { 
  int i = 0;  
  if(fp) {    
    fprintf(fp, "\nsize: %d\n\n", P->size);
    for(i = 0; i < P->size; i++) {      
      fprintf(fp, "(%.3f %.3f)\n",P->point[i]->x, P->point[i]->y);
    }
  }
}

int write_simplex_list(char *filename, simplex_list *sl, point_set *P) {	
  simplex_index *simp = NULL;
  FILE *fp = fopen(filename,"w");
  if (!fp)
    return 0;

  //  printf("\nWriting simplex list to file %s.\n\n", filename);  

  if (!sl || !P || !filename) return 0;

  fprintf(fp, "%d\n\n", sl->size);
  while (extract_simplex(&simp,sl)){		  
    fprintf(fp, "(%.3f, %.3f)(%.3f, %.3f)(%.3f, %.3f)\n",
        P->base_point[simp->index[0]].x, P->base_point[simp->index[0]].y,
        P->base_point[simp->index[1]].x, P->base_point[simp->index[1]].y,
        P->base_point[simp->index[2]].x, P->base_point[simp->index[2]].y);

    // Alocated in insert_simplex
    free(simp);
  }  
  fclose(fp);
  return 1;
}



