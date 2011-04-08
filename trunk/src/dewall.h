#include "simplex.h"
#include "unigrid.h"

//Debug trick
#define MAX_REC_LEVEL 30000
#define LOGGER printf("[%s - %s] : file %s, line %d\n", __DATE__, __TIME__, __FILE__,__LINE__)
#define MIN_UG_SIZE 5
#define LIMIT_OMP 2 // make studies to decide which is the best value

void deWall(point_set *P, face_list *AFL, simplex_list *SL, Axis ax, int rec_level);
int pointset_partition(point_set *P, plane* alpha, Axis ax, point_set *P1, point_set *P2);
int make_first_simplex(point_set *P, simplex **s);
int make_simplex(face *f, point_set *P, simplex **s);

void par_deWall(point_set *P, face_list *AFL, simplex_list *SL, Axis ax, int rec_level);
