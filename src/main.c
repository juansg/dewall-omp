#include "dewall.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>


// Globals to save their values when getting SIGSEGV
point_set P;
simplex_list SL;

void signal_handler(int sig){
  printf("Got a SIGSEGV, something went wrong! Saving the current "
      "triangulation to error_simplex.txt\n");
  write_simplex_list("error_simplex.txt", &SL, &P);
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
  face_list AFL;
  struct timeval start_time, end_time;

  // Do not abort immeditely, save the triangles!
  signal(SIGSEGV, signal_handler);

  if (argc < 3 || strcmp(argv[1], "-h") == 0)
    printf("Usage: dewall <input_file> <output_file>\n");
  else {
    if (read_points(argv[1], &P) == -1) {
      printf("Failed to read input points.\n");
      exit(EXIT_FAILURE);
    } else if (P.size < 3) {
      printf("Not enough points to triangulate: %d.\n", P.size);
    }

    initialize_face_list(&AFL, P.size/4);
    initialize_simplex_list(&SL, P.size/2);

    int total_usecs;
    gettimeofday(&start_time, NULL);

    par_deWall(&P, &AFL, &SL, XAxis, 0);

    gettimeofday(&end_time, NULL); 
    total_usecs = (end_time.tv_sec-start_time.tv_sec) * 1000000 +
      (end_time.tv_usec-start_time.tv_usec);
    printf("%d uSec\n", total_usecs);	

    // -----------------------------------

    write_simplex_list(argv[2], &SL, &P);
  }
  exit(EXIT_SUCCESS);
}
