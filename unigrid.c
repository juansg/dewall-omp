#include "simplex.h"
#include "unigrid.h"

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

  if (UG->sizeX < 0 || UG->sizeY < 0 || UG->grid_size == 0.0 )
    return 0;

  UG->c = (cell **)calloc(UG->sizeX * UG->sizeY, sizeof(cell *));   

  for (i = 0; i < P->size; i++) {
    cell *c = (cell *) malloc(sizeof(cell));
    if (!c) return 0;

    xGrid = (int) ((P->point[i]->x - UG->min_point.x) / UG->grid_size);
    yGrid = (int) ((P->point[i]->y - UG->min_point.y) / UG->grid_size);      		

    // Make sure the calculated index is in array bounds	
    xGrid = (xGrid < UG->sizeX-1)? xGrid : UG->sizeX-1;
    yGrid = (yGrid < UG->sizeY-1)? yGrid : UG->sizeY-1;

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

void calc_full_box(face *f, uniform_grid *UG, cell_index *start, cell_index *end, cell_index *dir){
  if(f->point[0]->x * f->point[1]->x > 0){
    dir->x = -1;
    start->x= UG->sizeX-1;
    end->x = 0;       
  } else {
    dir->x=  1;
    start->x = 0;      
    end->x = UG->sizeX-1;
  }

  if(f->point[0]->y * f->point[1]->y > 0){
    dir->y = -1;
    start->y = UG->sizeY-1;
    end->y = 0;
  } else {
    dir->y =  1;   
    start->y = 0;
    end->y = UG->sizeY-1;
  }
}

int in_halfspace(int x, int y, face *f, uniform_grid *UG){
  point p;
  p.x = x * UG->grid_size + UG->min_point.x;
  p.y = y * UG->grid_size + UG->min_point.y;
  return (pointLocationRelativeToFace(f, &p) == 1);
}

int scan_full_box(face *f, uniform_grid *UG, cell_index *start, cell_index *end, 
    cell_index *dir, point **p, float *min_rad){
  int i=0,j=0;
  int cell_index;
  cell *c;
  float rad;

  point *pp = NULL;
  int found = 0;

  for(i = start->x; dir->x*i <= dir->x*end->x; i += dir->x){
    for(j= start->y; dir->y*j <= dir->y*end->y; j += dir->y) {
      cell_index = i + j*UG->sizeX;			
      c = UG->c[cell_index];
      while(c) {
        pp = c->p;
        if (f->point[0] != pp && f->point[1] != pp 
            && pointLocationRelativeToFace(f,pp) == 1){
          rad = circumCircleRadius(f->point[0],f->point[1],pp);
          if(rad > 0 && rad < *min_rad) {
            *min_rad = rad;    
            *p = pp;    
            found = 1;     
          }
        } 
        c = c->next;
      }						 			
    }
  }	
  return found; 
}

float calc_box(face *f, uniform_grid *UG, cell_index *start, cell_index *end, float radius){
  point centre;
  float face_radius;
  float offset;

  face_radius = distance(f->point[0], f->point[1])/2;

  offset = sqrt(radius*radius - face_radius*face_radius);

  centre.x = (f->point[0]->x + f->point[1]->x)/2 + /*Lc->Lv.x **/ offset;
  centre.y = (f->point[0]->y + f->point[1]->y)/2 + /*Lc->Lv.y **/ offset;

  start->x = (int)((centre.x - UG->min_point.x - radius)/UG->grid_size);
  start->y = (int)((centre.y - UG->min_point.y - radius)/UG->grid_size);

  end->x = (int)((centre.x - UG->min_point.x + radius)/UG->grid_size);
  end->y = (int)((centre.y - UG->min_point.y + radius)/UG->grid_size);

  // Make sure the calculated index is in array bounds
  start->x = (start->x > 0)? start->x : 0;
  start->y = (start->y > 0)? start->y : 0;

  end->x = (end->x < UG->sizeX-1)? end->x : UG->sizeX-1;
  end->y = (end->y < UG->sizeY-1)? end->y : UG->sizeY-1;

  return radius*radius;
}

float scan_box(face *f, uniform_grid *UG, cell_index *start, cell_index *end, 
    point **p, float *min_rad){
  int i,j;
  int cell_index;
  cell *c;
  float rad;

  point *pp = NULL;
  int found = 0;

  for(i = start->x; i <= end->x; i++)
    for(j = start->y; j<= end->y; j++){
      cell_index = i + j * UG->sizeX;
      c = UG->c[cell_index];
      while(c) {
        pp = c->p;
        if (f->point[0] != pp && f->point[1] != pp 
            && pointLocationRelativeToFace(f,pp) == 1){
          rad = circumCircleRadius(f->point[0],f->point[1],pp);
          if(rad > 0 && rad < *min_rad) {
            *min_rad = rad;    
            *p = pp;    
            found = 1;     
          }
        } 
        c = c->next;
      }		
    }	
  return found;
}

int make_simplex_ug(face *f, point_set *P, simplex **s, uniform_grid *UG){
  int i, found = 0, min_index = -1;
  float min_radius = MAX_RADIUS;   
  float face_radius, box_radius, cellbox_radius = 0;
  cell_index c1, c2, dir;
  point *p;

  if (P->size < 1) return 0;

  face_radius = distance(f->point[0], f->point[1])/2.0;

  do {
    cellbox_radius++;
    box_radius = calc_box(f, UG, &c1, &c2, cellbox_radius*face_radius);
    found = scan_box(f, UG, &c1, &c2, &p, &min_radius);
  } while(!found && cellbox_radius <= 2);

  //  make a security scan of a box with radius = point dd distance
  if(found && min_radius > box_radius){  
    box_radius = calc_box(f, UG, &c1, &c2, sqrt(min_radius));
    scan_box(f, UG, &c1, &c2, &p, &min_radius);
  }

  // If could not find point, scans entire grid
  if(!found) {
    calc_full_box(f, UG, &c1, &c2, &dir);
    found = scan_full_box(f, UG, &c1, &c2, &dir, &p, &min_radius);
  } 

  if (!found)
    return 0;

  build_simplex(s, f, p);    
  return 1;
}
