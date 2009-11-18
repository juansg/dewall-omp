#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simplex.h"

//Debug trick
#define LOGGER printf("[%s - %s] : file %s, line %d\n", __DATE__, __TIME__, __FILE__,__LINE__)

//TODO: create real list initialization
#define empty_list NULL

void deWall(point_set *P, face_list *AFL, simplex_list *SL, Axis ax);
