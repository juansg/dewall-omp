#include <stdio.h>
#include "../../dewall.h"

void test_pointLocationRelativeToFace();

int main(){
  point_set P;
  point centre;
  float radius;

  face f;
  int loc;

  if (read_points("test_geometry.p", &P) == -1)
    printf("\nFailed to read input points.\n");
  else {
    print_points(stdout, &P);
    if (P.size >= 3){ 
      printf ("\ndistance(p1,p2) = %f", distance(&(P.point[0]),&(P.point[1])));
      printf ("\ndistance(p1,p3) = %f", distance(&(P.point[0]),&(P.point[2])));
      printf ("\ndistance(p2,p3) = %f\n", distance(&(P.point[1]),&(P.point[2])));
      printf ("\ncircumCircleRadius(p1,p2,p3) = %f\n", 
              circumCircleRadius(&(P.point[0]),&(P.point[1]),&(P.point[2])));


      if (circumCircleCentre(&(P.point[0]),&(P.point[1]),&(P.point[2]),&centre))
        printf("\ncircumCircleCentre(p1,p2,p3) = (%f,%f)", centre.x, centre.y);

      if (circumCircleCentreAndRadius(&(P.point[0]),&(P.point[1]),&(P.point[2]),
              &centre, &radius))
        printf("\ncircumCircleCentreAndRadius(p1,p2,p3,center,rad) = (%f,%f), "
              "radius = %f\n", centre.x, centre.y, radius);

      f.point[0] = &(P.point[0]);
      f.point[1] = &(P.point[1]);
      loc = pointLocationRelativeToFace(&f, &(P.point[2]));
      printf("\nPoint (%f, %f) is %s the face [(%f, %f)(%f, %f)] (loc = %d)",
         P.point[2].x, P.point[2].y, loc? (loc == 1? "above": "below") : "on",
         f.point[0]->x, f.point[0]->y, f.point[1]->x, f.point[1]->y, loc);

      f.point[0] = &(P.point[1]);
      f.point[1] = &(P.point[2]);
      loc = pointLocationRelativeToFace(&f, &(P.point[0]));
      printf("\nPoint (%f, %f) is %s the face [(%f, %f)(%f, %f)] (loc = %d)",
         P.point[0].x, P.point[0].y, loc? (loc == 1? "above": "below") : "on",
         f.point[0]->x, f.point[0]->y, f.point[1]->x, f.point[1]->y, loc);
      
      f.point[0] = &(P.point[2]);
      f.point[1] = &(P.point[0]);
      loc = pointLocationRelativeToFace(&f, &(P.point[1]));
      printf("\nPoint (%f, %f) is %s the face [(%f, %f)(%f, %f)] (loc = %d)",
         P.point[1].x, P.point[1].y, loc? (loc == 1? "above": "below") : "on",
         f.point[0]->x, f.point[0]->y, f.point[1]->x, f.point[1]->y, loc);      

      } 
   }
  test_pointLocationRelativeToFace();
  return 0;
}

void test_pointLocationRelativeToFace(){
   printf("\n\n--- test_pointLocationRelativeToFace ---\n");
   point a, b, c;
   face f;
   int loc;

   a.x = b.y = 5;
	a.y = b.x = 10;

	f.point[0] = &a;
	f.point[1] = &b;   

	c.x = c.y = 5;
   loc = pointLocationRelativeToFace(&f, &c);
   printf("\nPoint (%f, %f) is %s the face [(%f, %f)(%f, %f)] (loc = %d)",
      c.x, c.y, loc? (loc == 1? "above": "below") : "on",
      f.point[0]->x, f.point[0]->y, f.point[1]->x, f.point[1]->y, loc);

  	c.x = c.y = 7.5;
   loc = pointLocationRelativeToFace(&f, &c);
   printf("\nPoint (%f, %f) is %s the face [(%f, %f)(%f, %f)] (loc = %d)",
      c.x, c.y, loc? (loc == 1? "above": "below") : "on",
      f.point[0]->x, f.point[0]->y, f.point[1]->x, f.point[1]->y, loc);

	c.x = c.y = 15;
   loc = pointLocationRelativeToFace(&f, &c);
   printf("\nPoint (%f, %f) is %s the face [(%f, %f)(%f, %f)] (loc = %d)\n\n",
      c.x, c.y, loc? (loc == 1? "above": "below") : "on",
      f.point[0]->x, f.point[0]->y, f.point[1]->x, f.point[1]->y, loc);

}
