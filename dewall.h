#include "simplex.h"
#include "unigrid.h"

//Debug trick
#define LOGGER printf("[%s - %s] : file %s, line %d\n", __DATE__, __TIME__, __FILE__,__LINE__)
#define MIN_UG_SIZE 2

void deWall(point_set *P, face_list *AFL, simplex_list *SL, Axis ax, int rec_level);
void pointset_partition(point_set *P, plane* alpha, Axis ax, point_set *P1, point_set *P2);
int make_first_simplex(point_set *P, simplex **s);
int make_simplex(face *f, point_set *P, simplex **s);

