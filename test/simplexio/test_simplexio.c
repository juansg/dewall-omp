#include <stdio.h>
#include "../../dewall.h"

int main(){
  point_set P;
  if (read_points("test_simplexio.p", &P) == -1)
    printf("Failed to read input points.\n");
  else
    print_points(stdout, &P);
  return 0;
}
