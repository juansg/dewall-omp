#include <stdio.h>
#include "../../dewall.h"

void print_list(FILE *fp, list *l);
int equal_points(void *vp1, void *vp2);
int hash_points(void *vp1);

int main() {
  point_set P;
  list l;
  int i = 0;

  if (read_points("test_hashlist.p", &P) == -1)
    printf("Failed to read input points.\n");
  else {
    initialize_list(&l,sizeof(point *),equal_points);
    hash_list(&l, P.size/4, hash_points);

    // Insert elements into the list
    for (i = 0; i < P.size; i++)
      if (!insert_list(&l, &(P.point[i])))
        printf("\nCould not insert element P->point[%d] in the hash list.\n", i);    

    // Print list  
    print_list(stdout,&l);

    // Remove elements from list (even: first element, odd: last element)
    while (l.size) {
      if (l.size % 2) {
        printf("\nRemoved the first element:") ;
        l.current = l.first;
      } else {
        l.current = l.last;
        printf("\nRemoved the last element:") ;
      }
      delete_current_list(&l);
      print_list(stdout,&l);
    }    

  }
  return 0;
}

void print_list(FILE *fp, list *l) {
  printf("\nList size = %d\n", l->size);
  list_element *curr = l->first;
  point *p = NULL;
  while (curr) {
    p = (point *)curr->obj;
    if (p)
      fprintf(fp, "(%f, %f)\n", p->x, p->y);
    curr = curr->next;
  }
}

int equal_points(void *vp1, void *vp2)  {
  point *p1 = (point *) vp1;
  point *p2 = (point *) vp2;  

  if (p1->x == p2->x && p1->y == p2->y)
    return 1;
  else
    return 0;
}

int hash_points(void *vp1) {
  point *p1 = (point *) vp1;
  return (int)((long)(p1->x) ^ (long)(p1->y));

}



