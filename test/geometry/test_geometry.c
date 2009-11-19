#include <stdio.h>
#include "../../simplex.h"

int main(){
  point_set P;
  if (read_points("test_geometry.p", &P) == -1)
    printf("\nFailed to read input points.\n");
  else
    print_points(stdout, &P);
    if (P.size >= 3){ 
      printf ("\ndistance(p1,p2) = %f\n", distance(&(P.point[0]),&(P.point[1])));
      printf ("\ndistance(p1,p3) = %f\n", distance(&(P.point[0]),&(P.point[1])));
      printf ("\ndistance(p2,p3) = %f\n", distance(&(P.point[0]),&(P.point[1])));
      printf ("\ncircumCircleRadius(p1,p2,p3) = %f\n", circumCircleRadius(&(P.point[0]),&(P.point[1]),&(P.point[2])));   
    } else 
         printf("\nSorry! I need minimum 3 points to try the geometric operations.\n");
  return 0;
}
