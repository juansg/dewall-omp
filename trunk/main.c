#include "dewall.h"

int main(int argc, char *argv[]) {
	point_set P;
	face_list AFL;
	simplex_list SL;

	point a, b, c;

	//	a.x = -0.145802;
	//	a.y = -0.494293;
	//	b.x = 0.059801;
	//	b.y = -0.257012;
	//	c.x = 0.059801;
	//	c.y = -0.257012;

	//	a.x = -0.145802;
	//	a.y = -0.494293;
	//	b.x = 0.059801;
	//	b.y = -0.257012;
	//	c.x = -0.059252;
	//	c.y = 0.158193;

	a.x = 0;
	a.y = 0;
	b.x = 6;
	b.y = 0;
	c.x = 3;
	c.y = 3;

	point *centro = circumCircleCentre(&a, &b, &c);

	printf("raio=%f\n", circumCircleRadius(&a, &b, &c));
	printf("centro=(%f,%f)\n", centro->x, centro->y);

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
