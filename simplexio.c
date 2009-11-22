#include <stdio.h>
#include <stdlib.h>
#include "simplex.h"


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
  if (fp)
    print_points(fp, P);  
  else 
    return -1;
  return 0;
 }

void print_points (FILE *fp, point_set *P) { 
  int i = 0;  
  if(fp) {    
    fprintf(fp, "\nsize: %d\n\n", P->size);
    for(i = 0; i < P->size; i++) {      
          fprintf(fp, "(%f %f)\n",P->point[i].x, P->point[i].y);
    }
  }
}

int write_simplex_list(char *filename, simplex_list *s)
{
 //TODO: implement function logic
  printf("\nwrite_simplex_list function not implemented!\n");
 return 0;
}



