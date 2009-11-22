#include "dewall.h"
#include "hashlist.h"

int main(int argc, char *argv[]) {
	point_set P;
	face_list AFL;
	simplex_list SL;

	if (argc < 3 || strcmp(argv[1], "-h") == 0)
		printf("Usage: dewall <input_file> <output_file>\n");
	else {
		if (read_points(argv[1], &P) == -1) {
			printf("Failed to read input points.\n");
			exit(EXIT_FAILURE);
		}

		//TODO: create real list initialization
		AFL = empty_list;
		SL = empty_list;

		// ---- Calculate time from here -----
		deWall(&P, &AFL, &SL, XAxis);
		// -----------------------------------

		write_simplex_list(argv[2], &SL);
	}
	exit(EXIT_SUCCESS);
}
