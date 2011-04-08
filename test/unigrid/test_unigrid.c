#include <stdio.h>
#include "../../dewall.h"

void print_list(FILE *fp, list *l);
int equal_points(void *vp1, void *vp2);
int hash_points(void *vp1);

int main() {
  point_set P;
  list l;
  int i = 0;

  if (read_points("test_unigrid.p", &P) == -1)
    printf("Failed to read input points.\n");
  else {
    uniform_grid UG;
    createUniformGrid(&P,&UG);
    print_points(stdout, &P);
    print_uniform_grid(&UG);
  }
  return 0;
}




