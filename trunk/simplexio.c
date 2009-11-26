#include <stdio.h>
#include <stdlib.h>
#include "simplex.h"

//Debug trick
#define LOGGER printf("[%s - %s] : file %s, line %d\n", __DATE__, __TIME__, __FILE__,__LINE__)


int read_points(char *filename, point_set *P) {
  FILE *fp;
  int i = -1;
  point p;

  fp=fopen(filename,"r");
  if(fp) {
    fscanf(fp,"%d",&(P->size));
    P->point = (point *)malloc(sizeof(point)*P->size);
    if(P->point)
      for(i = 0; i < P->size; i++) {
         fscanf(fp,"%f %f",&(P->point[i].x),&(P->point[i].y));
         #ifdef DEBUG
            printf("%f %f\n",P->point[i].x, P->point[i].y);
         #endif
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
          fprintf(fp, "(%.3f %.3f)\n",P->point[i].x, P->point[i].y);
    }
  }
}

int write_simplex_list(char *filename, simplex_list *sl) {	
  char *simp = NULL;
  FILE *fp = fopen(filename,"w");
  if (!fp)
    return 0;
    
  printf("\nWriting simplex list to file %s.\n\n", filename);  

  fprintf(fp, "%d\n\n", sl->size);
  while (sl->size > 0){
	    if (extract_simplex(&simp,sl))		  
          fprintf(fp, "%s\n", simp);
  }
  
  fclose(fp);
  return 1;
}



