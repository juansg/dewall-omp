#include "dewall.h"

/* Functions not implemented yet!!!*/

int make_first_simplex(point_set *P, plane *alpha, simplex *s){return 0;}
int make_simplex(face *f, point_set *P, simplex *s){return 0;}

void deWall(point_set *P, face_list *AFL, simplex_list *SL, Axis ax)
{
   //TODO: implement function logic   
   printf("\ndeWall function not fully implemented!\n");
   print_points(stdout, P);
   printf("Axis: %s\n", ax?"Y":"X");

   face f;
	face f1;
	face_list AFLa, AFL1, AFL2;

	plane alpha;
	simplex t;
	point_set P1, P2;

  int i = 0;

  initialize_face_list(&AFLa);
  initialize_face_list(&AFL1);
  initialize_face_list(&AFL2);
    
  printf("\npointset_partition initiated!\n");
  pointset_partition(P,&alpha,ax,&P1,&P2);
  print_points(stdout, &P1);
  print_points(stdout, &P2);
	
	/* Simple Wall Construction */

  // Building the first simplex
	if (AFL == NULL){
	    if (make_first_simplex(P,&alpha,&t)){
         for(i = 0; i < 3; i++) 
            insert_list(&(t.face[i]),AFL);	
	      insert_simplex(&t,SL);
      }
	}

  // Dividing the faces in 3 lists
	while (extract_list(&f,AFL)){
        switch (intersect(&f,&alpha)) {
            case  0: insert_list(&f, &AFLa); break;
            case  1: insert_list(&f, &AFL1); break;
            case -1: insert_list(&f, &AFL2); break;
        }
	}
	
  // Building the wall for the faces in the middle
	while(AFLa != NULL){
        extract_list(&f,&AFLa);
        if (make_simplex(&f, P, &t)){
            insert_simplex(&t,SL);
            for(i = 0; i < 3 /*&& (t.face[i] != f)*/; i++){
                switch (intersect(&(t.face[i]),&alpha)) {
                    case  0: update_face(&(t.face[i]), &AFLa); break;
                    case  1: update_face(&(t.face[i]), &AFL1); break;
                    case -1: update_face(&(t.face[i]), &AFL2); break;
                }
            }  
        }		
	}

  /* Recursive Triangulation */
	#pragma omp task
	if (AFL1 != NULL)
		deWall(&P1, &AFL1, SL, invert_axis(ax));
	#pragma omp task
	if (AFL2 != NULL)
		deWall(&P2, &AFL2, SL, invert_axis(ax));

   //Free Lists...
  
}

void pointset_partition(point_set *P, plane* alpha, Axis ax, point_set *P1, point_set *P2){
 switch(ax)
  {
   case XAxis :	qsort((void *)P->point, (size_t)P->size, sizeof(point), compare_points_X);
		alpha->normal.x = 1;      
      //calculates plane position from central elements (n/2)-1 and (n/2)
		alpha->off = (P->point[P->size/2-1].x + P->point[P->size/2].x)/2;
		break;

   case YAxis : qsort((void *)P->point, (size_t)P->size, sizeof(point), compare_points_Y);
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
   


