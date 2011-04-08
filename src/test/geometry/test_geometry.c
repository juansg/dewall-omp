#include <stdio.h>
#include "../../dewall.h"

void test_pointLocationRelativeToFace();

int main() {
  point_set P;
  point centre;
  float radius;

  face f;
  int loc;

  if (read_points("test_geometry.p", &P) == -1)
    printf("\nFailed to read input points.\n");
  else {
    print_points(stdout, &P);
    if (P.size >= 3) {
      printf("\ndistance(p1,p2) = %.3f", distance(&(P.base_point[0]),
            &(P.base_point[1])));
      printf("\ndistance(p1,p3) = %.3f", distance(&(P.base_point[0]),
            &(P.base_point[2])));
      printf("\ndistance(p2,p3) = %.3f\n", distance(&(P.base_point[1]),
            &(P.base_point[2])));
      printf("\ncircumCircleRadius(p1,p2,p3) = %.3f\n", circumCircleRadius(
            &(P.base_point[0]), &(P.base_point[1]), &(P.base_point[2])));

      if (circumCircleCentre(&(P.base_point[0]), &(P.base_point[1]), &(P.base_point[2]),
            &centre))
        printf("\ncircumCircleCentre(p1,p2,p3) = (%.3f,%.3f)", centre.x,
            centre.y);

      if (circumCircleCentreAndRadius(&(P.base_point[0]), &(P.base_point[1]),
            &(P.base_point[2]), &centre, &radius))
        printf(
            "\ncircumCircleCentreAndRadius(p1,p2,p3,center,rad) = (%.3f,%.3f), "
            "radius = %.3f\n", centre.x, centre.y, radius);

      f.point[0] = &(P.base_point[0]);
      f.point[1] = &(P.base_point[1]);
      loc = pointLocationRelativeToFace(&f, &(P.base_point[2]));
      printf(
          "\nPoint (%.3f, %.3f) is on the %s of the face [(%.3f, %.3f)(%.3f, %.3f)] (loc = %d)",
          P.base_point[2].x, P.base_point[2].y, loc ? (loc == 1 ? "right"
            : "left") : "top", f.point[0]->x, f.point[0]->y,
          f.point[1]->x, f.point[1]->y, loc);

      f.point[0] = &(P.base_point[1]);
      f.point[1] = &(P.base_point[2]);
      loc = pointLocationRelativeToFace(&f, &(P.base_point[0]));
      printf(
          "\nPoint (%.3f, %.3f) is on the %s of the face [(%.3f, %.3f)(%.3f, %.3f)] (loc = %d)",
          P.base_point[0].x, P.base_point[0].y, loc ? (loc == 1 ? "right"
            : "left") : "top", f.point[0]->x, f.point[0]->y,
          f.point[1]->x, f.point[1]->y, loc);

      f.point[0] = &(P.base_point[2]);
      f.point[1] = &(P.base_point[0]);
      loc = pointLocationRelativeToFace(&f, &(P.base_point[1]));
      printf(
          "\nPoint (%.3f, %.3f) is on the %s of the face [(%.3f, %.3f)(%.3f, %.3f)] (loc = %d)",
          P.base_point[1].x, P.base_point[1].y, loc ? (loc == 1 ? "right"
            : "left") : "top", f.point[0]->x, f.point[0]->y,
          f.point[1]->x, f.point[1]->y, loc);

    }
  }
  test_pointLocationRelativeToFace();
  return 0;
}

void test_pointLocationRelativeToFace() {
  printf("\n\n--- test_pointLocationRelativeToFace ---\n");
  point a, b, c;
  face f;
  int loc;

  //line with negative slope
  a.x = b.y = 5;
  a.y = b.x = 10;

  f.point[0] = &a;
  f.point[1] = &b;

  c.x = c.y = 5;
  loc = pointLocationRelativeToFace(&f, &c);
  printf(
      "\nPoint (%.3f, %.3f) is on the %s of the face [(%.3f, %.3f)(%.3f, %.3f)] (loc = %d)",
      c.x, c.y, loc ? (loc == 1 ? "left" : "right") : "top",
      f.point[0]->x, f.point[0]->y, f.point[1]->x, f.point[1]->y, loc);

  c.x = c.y = 7.5;
  loc = pointLocationRelativeToFace(&f, &c);
  printf(
      "\nPoint (%.3f, %.3f) is on the %s of the face [(%.3f, %.3f)(%.3f, %.3f)] (loc = %d)",
      c.x, c.y, loc ? (loc == 1 ? "left" : "right") : "top",
      f.point[0]->x, f.point[0]->y, f.point[1]->x, f.point[1]->y, loc);

  c.x = c.y = 15;
  loc = pointLocationRelativeToFace(&f, &c);
  printf(
      "\nPoint (%.3f, %.3f) is on the %s of the face [(%.3f, %.3f)(%.3f, %.3f)] (loc = %d)\n\n",
      c.x, c.y, loc ? (loc == 1 ? "left" : "right") : "top",
      f.point[0]->x, f.point[0]->y, f.point[1]->x, f.point[1]->y, loc);

  //line with positive slope
  a.x = a.y = 5;
  b.x = b.y = 10;

  f.point[0] = &a;
  f.point[1] = &b;

  c.x = 5;
  c.y = 2;
  loc = pointLocationRelativeToFace(&f, &c);
  printf(
      "\nPoint (%.3f, %.3f) is on the %s of the face [(%.3f, %.3f)(%.3f, %.3f)] (loc = %d)",
      c.x, c.y, loc ? (loc == 1 ? "left" : "right") : "top",
      f.point[0]->x, f.point[0]->y, f.point[1]->x, f.point[1]->y, loc);

  c.x = c.y = 15;
  loc = pointLocationRelativeToFace(&f, &c);
  printf(
      "\nPoint (%.3f, %.3f) is on the %s of the face [(%.3f, %.3f)(%.3f, %.3f)] (loc = %d)",
      c.x, c.y, loc ? (loc == 1 ? "left" : "right") : "top",
      f.point[0]->x, f.point[0]->y, f.point[1]->x, f.point[1]->y, loc);

  c.x = 10;
  c.y = 15;
  loc = pointLocationRelativeToFace(&f, &c);
  printf(
      "\nPoint (%.3f, %.3f) is on the %s of the face [(%.3f, %.3f)(%.3f, %.3f)] (loc = %d)\n\n",
      c.x, c.y, loc ? (loc == 1 ? "left" : "right") : "top",
      f.point[0]->x, f.point[0]->y, f.point[1]->x, f.point[1]->y, loc);

  //vertical line
  a.x = b.x = 5;
  a.y = 5;
  b.y = 10;

  f.point[0] = &a;
  f.point[1] = &b;

  c.x = 6;
  c.y = 2;
  loc = pointLocationRelativeToFace(&f, &c);
  printf(
      "\nPoint (%.3f, %.3f) is on the %s of the face [(%.3f, %.3f)(%.3f, %.3f)] (loc = %d)",
      c.x, c.y, loc ? (loc == 1 ? "left" : "right") : "top",
      f.point[0]->x, f.point[0]->y, f.point[1]->x, f.point[1]->y, loc);

  c.x = c.y = 4;
  loc = pointLocationRelativeToFace(&f, &c);
  printf(
      "\nPoint (%.3f, %.3f) is on the %s of the face [(%.3f, %.3f)(%.3f, %.3f)] (loc = %d)",
      c.x, c.y, loc ? (loc == 1 ? "left" : "right") : "top",
      f.point[0]->x, f.point[0]->y, f.point[1]->x, f.point[1]->y, loc);

  c.x = 5;
  c.y = 15;
  loc = pointLocationRelativeToFace(&f, &c);
  printf(
      "\nPoint (%.3f, %.3f) is on the %s of the face [(%.3f, %.3f)(%.3f, %.3f)] (loc = %d)\n\n",
      c.x, c.y, loc ? (loc == 1 ? "left" : "right") : "top",
      f.point[0]->x, f.point[0]->y, f.point[1]->x, f.point[1]->y, loc);

  //horizontal line
  a.x = 5;
  b.x = 10;
  a.y = b.y = 5;

  f.point[0] = &a;
  f.point[1] = &b;

  c.x = c.y = 6;
  loc = pointLocationRelativeToFace(&f, &c);
  printf(
      "\nPoint (%.3f, %.3f) is on the %s of the face [(%.3f, %.3f)(%.3f, %.3f)] (loc = %d)",
      c.x, c.y, loc ? (loc == 1 ? "left" : "right") : "top",
      f.point[0]->x, f.point[0]->y, f.point[1]->x, f.point[1]->y, loc);

  c.x = c.y = 4;
  loc = pointLocationRelativeToFace(&f, &c);
  printf(
      "\nPoint (%.3f, %.3f) is on the %s of the face [(%.3f, %.3f)(%.3f, %.3f)] (loc = %d)",
      c.x, c.y, loc ? (loc == 1 ? "left" : "right") : "top",
      f.point[0]->x, f.point[0]->y, f.point[1]->x, f.point[1]->y, loc);

  c.x = 15;
  c.y = 5;
  loc = pointLocationRelativeToFace(&f, &c);
  printf(
      "\nPoint (%.3f, %.3f) is on the %s of the face [(%.3f, %.3f)(%.3f, %.3f)] (loc = %d)\n\n",
      c.x, c.y, loc ? (loc == 1 ? "left" : "right") : "top",
      f.point[0]->x, f.point[0]->y, f.point[1]->x, f.point[1]->y, loc);

}
