#include "dewall.h"
#include <stdio.h>

void print_face_list(FILE *fp, face_list *l) {
	printf("\nList size = %d\n", l->size);
    list_element *curr = l->first;
    face *f = NULL;
    while (curr) {
      f = (face *)curr->obj;
      if (f)
        fprintf(stdout, "face: (%.3f, %.3f); (%.3f, %.3f)\n", 
        f->point[0]->x, f->point[0]->y, f->point[1]->x, f->point[1]->y); 
      curr = curr->next;
    }
}

void print_simplex_list(FILE *fp, simplex_list *l, point_set *P) {
	 printf("\nList size = %d\n", l->size);
    list_element *curr = l->first;
    char *simp = NULL;
    while (curr) {
      simp = (char *)curr->obj;
      if (simp)
         fprintf(fp, "%s\n", simp);
      curr = curr->next;
    }
}

void deWall(point_set *P, face_list *AFL, simplex_list *SL, Axis ax) {
   printf("\n--------------------------------------------");
   printf("\nP:");
   print_points(stdout, P);
   printf("Axis: %s\n", ax?"Y":"X");
	
   face *f;
   face_list AFLa, AFL1, AFL2;

   plane alpha;
   simplex *t;
   point_set P1, P2;

   int i = 0;

  initialize_face_list(&AFLa, P->size/4);
  initialize_face_list(&AFL1, P->size/4);
  initialize_face_list(&AFL2, P->size/4);
    
  pointset_partition(P,&alpha,ax,&P1,&P2);
  printf("\nP1:");
  print_points(stdout, &P1);
  printf("\nP2:");
  print_points(stdout, &P2);
	
	/* Simple Wall Construction */

	if (AFL->size == 0){
	    if (make_first_simplex(P,&t)){
         for(i = 0; i < 3; i++) 
            insert_face(t->face[i],AFL);	
	      insert_simplex(t,SL,P);
      }
	}
	printf("\nAFL:");
	print_face_list(stdout, AFL);
	
  // Dividing the faces in 3 lists
	while (extract_face(&f,AFL)){
        switch (intersect(f,&alpha)) {
            case  0: insert_face(f, &AFLa); break;
            case -1: insert_face(f, &AFL1); break;
            case  1: insert_face(f, &AFL2); break;
        }
	}
	
	printf("\nAFLa:");
	print_face_list(stdout, &AFLa);
  printf("\nAFL1:");
	print_face_list(stdout, &AFL1);
  printf("\nAFL2:");
	print_face_list(stdout, &AFL2);
	
  // Building the wall for the faces in the middle
	while(AFLa.size > 0){
        extract_face(&f,&AFLa);
        if (make_simplex(f, P, &t)){           
            for(i = 0; i < 3; i++){                
                if (!equal_face(t->face[i], f)){
                  printf("\nFace to insert: (%.3f, %.3f)(%.3f, %.3f)", 
                  t->face[i]->point[0]->x, t->face[i]->point[0]->y,
                  t->face[i]->point[1]->x, t->face[i]->point[1]->y);
                   switch (intersect(t->face[i],&alpha)) {
                       case  0: update_face(t->face[i], &AFLa); break;
                       case -1: update_face(t->face[i], &AFL1); break;
                       case  1: update_face(t->face[i], &AFL2); break;
                   }
                }               
            }  
            printf("\n");
            insert_simplex(t,SL,P);
        }		
	}

   printf("\nAFLa:");
	print_face_list(stdout, &AFLa);
   printf("\nAFL1:");
	print_face_list(stdout, &AFL1);
  	printf("\nAFL2:");
	print_face_list(stdout, &AFL2);

	printf("\n--------------------------------------------");
  /* Recursive Triangulation */
	#pragma omp task
	if (AFL1.size > 0)
		deWall(&P1, &AFL1, SL, invert_axis(ax));
	#pragma omp task
	if (AFL2.size > 0)
		deWall(&P2, &AFL2, SL, invert_axis(ax));
	
   //printf("\nSimplex list:");
   //print_simplex_list(stdout, SL);
   //Free Lists...
  
}

void pointset_partition(point_set *P, plane* alpha, Axis ax, point_set *P1, point_set *P2){
 switch(ax)
  {
   case XAxis :	qsort((void *)P->point, (size_t)P->size, sizeof(point), compare_points_X);
		alpha->normal.x = 1;      
		alpha->normal.y = 0;  
      //calculates plane position from central elements (n/2)-1 and (n/2)		
		alpha->off = (P->point[P->size/2-1].x + P->point[P->size/2].x)/2;
		break;

   case YAxis : qsort((void *)P->point, (size_t)P->size, sizeof(point), compare_points_Y);
		alpha->normal.x = 0;  
		alpha->normal.y = 1;
      //calculates plane position from central elements (n/2)-1 and (n/2)
		alpha->off = (P->point[P->size/2-1].y + P->point[P->size/2].y)/2;
		break;
  }
   // P1 contains the first half
   P1->size = P->size/2;
   P1->point = P->point;

   // P2 contains the remaining elements
   P2->size = P->size - P1->size;
   P2->point = &(P->point[P1->size]);
}

//Return the minimum distance, the minimum index is stored in *i
float minimum_distance(point *p, point_set *P, int start, int end, int *index){
   int i, min_index = -1;
   float dist, min_dist;   

   dist = min_dist = 999;

   for(i = start; i < end; i++) {
     dist = distance(p, &(P->point[i]));
     if(dist > 0 && dist < min_dist) {
         min_dist = dist;    
         min_index = i;         
     }
   }

   *index = min_index;
   return min_dist;
}

//Return the minimum radius, the minimum index is stored in *i
float minimum_radius(point *p1, point *p2, point_set *P, int start, int end, int *index){
   int i, min_index = -1;
   float rad, min_rad;   

   rad = min_rad = 999;

   for(i = start; i < end; i++) 
      if (p1 != &(P->point[i]) && p2 != &(P->point[i])){
        rad = circumCircleRadius(p1,p2,&(P->point[i]));
        if(rad > 0 && rad < min_rad) {
            min_rad = rad;    
            min_index = i;         
        }
   }

   *index = min_index;
   return min_rad;
}

int valid_index(point_set *P, int i){
   if (i < 0 || i >= P->size)
      return 0;
   else
      return 1;
}

int make_first_simplex(point_set *P, simplex **s){
   face f;
   point *p3;
   int min_index;
   
   // select the point p1 nearest to the plane 
   f.point[0] = &(P->point[P->size/2-1]);	

   // select a second point p2 such that p2 is the nearest point to p1 on the other side of alpha
   //printf("minimum distance: %.3f\n", minimum_distance(f.point[0], P, P->size/2, P->size, &min_index));
   minimum_distance(f.point[0], P, P->size/2, P->size, &min_index);
    if (!valid_index(P,min_index))
      return 0;
   f.point[1] = &(P->point[min_index]);
      
   // search the point p3 such that the circum-circle around the 1-face (p1, p2) and the point p3 has the minimum
   //radius

   //printf("minimum radius: %.3f\n", minimum_radius(f.point[0], f.point[1], P, 0, P->size, &min_index));
   minimum_radius(f.point[0], f.point[1], P, 0, P->size, &min_index);
  if (!valid_index(P,min_index))
      return 0;

   p3 = &(P->point[min_index]);      

   if (pointLocationRelativeToFace(&f,p3) != 1)
    revert_face(&f);

   build_simplex(s, &f, p3);
   revert_face((*s)->face[0]);    
   return 1;
}


int make_simplex(face *f, point_set *P, simplex **s){
	int i, min_index = -1;
   float rad, min_rad;   

   rad = min_rad = 999;
   
   for(i = 0; i < P->size; i++) 
      if (f->point[0] != &(P->point[i]) && f->point[1] != &(P->point[i]) 
         && pointLocationRelativeToFace(f,&(P->point[i])) == 1){
        rad = circumCircleRadius(f->point[0],f->point[1],&(P->point[i]));
        if(rad > 0 && rad < min_rad) {
            min_rad = rad;    
            min_index = i;         
        }
   }

   if (!valid_index(P, min_index))
      return 0;

   build_simplex(s, f, &(P->point[min_index]));    
   return 1;
}


   


