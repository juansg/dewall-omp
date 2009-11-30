#include "geometry.h"
#include "ug.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void bounding_box(point_set *P, uniform_grid *UG){
	UG->min_point.x = UG->max_point.x = P->point[0]->x;
	UG->min_point.y = UG->max_point.y = P->point[0]->y;

	int i;	
	for (i = 0; i < P->size; i++) {
      // x min
      if (P->point[i]->x < UG->min_point.x)
			UG->min_point.x = P->point[i]->x;
      
      // y min
      if (P->point[i]->y < UG->min_point.y)
			UG->min_point.y = P->point[i]->y;

      // x max
      if (P->point[i]->x > UG->max_point.x)
			UG->max_point.x = P->point[i]->x;

      // y max
      if (P->point[i]->y > UG->max_point.y)
			UG->max_point.y = P->point[i]->y;
   }

}

void gridSize(uniform_grid *UG, int size) {
	UG->grid_size = sqrt((
         ((UG->max_point.x - UG->min_point.x) * 
         (UG->max_point.y - UG->min_point.y))
          / size));

   // x res	
   UG->sizeX = (int)ceilf((UG->max_point.x - UG->min_point.x)/UG->grid_size); 

   // y res
   UG->sizeY = (int)ceilf((UG->max_point.y - UG->min_point.y)/UG->grid_size);

}

int createUniformGrid(point_set *P, uniform_grid *UG) {
   cell *c;
   int i, index, xGrid, yGrid;
   bounding_box(P,UG);
   gridSize(UG, P->size);
   
   UG->c = (cell **)calloc(UG->sizeX * UG->sizeY, sizeof(cell *));
   

   for (i = 0; i < P->size; i++) {
		cell *c = (cell *) malloc(sizeof(cell));
      if (!c) return 0;

		xGrid = (int) ((P->point[i]->x - UG->min_point.x) / UG->grid_size);
		yGrid = (int) ((P->point[i]->y - UG->min_point.y) / UG->grid_size);      		
      index = xGrid + yGrid * UG->sizeX;
          
      c->p = P->point[i];
      c->next = UG->c[index];
      UG->c[index] = c;
	} 
   return 1;
}

void print_uniform_grid(uniform_grid *UG){
   printf("\nUG sizeX: %d\n", UG->sizeX);
   printf("UG sizeY: %d\n", UG->sizeY);
   printf("UG gridsize: %f\n", UG->grid_size);

   printf("UG min point: (%.3f %.3f)\n", UG->min_point.x, UG->min_point.y);
   printf("UG max point: (%.3f %.3f)\n", UG->max_point.x, UG->max_point.y);

   int i, j, index;
   cell *c = NULL;
   for (i = 0; i < UG->sizeX; i++)
      for (j = 0; j < UG->sizeY; j++){
         printf("\nUG[%d][%d]: ", i, j);
         index = i + j * UG->sizeX;
         c = UG->c[index];
         while (c){
            printf("(%.3f %.3f) ", c->p->x, c->p->y);
            c = c->next;
         }
      }  
   printf("\n\n");
}
