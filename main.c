#include "dewall.h"
#include <stdio.h>
#include <stdlib.h>
#include "geometry.h"

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

		a.x = 5;
		a.y = 10;
		b.x = 10;
		b.y = 5;
		c.x = 15;
		c.y = 15;

		face *f = (face *) malloc(sizeof(face));
		f->point[0] = &a;
		f->point[1] = &b;

		if (pointLocationRelativeToFace(f, &c) == 1)
			printf("Ponto eh acima\n");
		if (pointLocationRelativeToFace(f, &c) == -1)
			printf("Ponto eh abaixo\n.");
		if (pointLocationRelativeToFace(f, &c) == 0)
			printf("Ponto intersecta a reta\n.");


	if (argc < 3 || strcmp(argv[1], "-h") == 0)
		printf("Usage: dewall <input_file> <output_file>\n");
	else {
		if (read_points(argv[1], &P) == -1) {
			printf("Failed to read input points.\n");
			exit(EXIT_FAILURE);
		}

		initialize_face_list(&AFL, P.size/4);
		initialize_simplex_list(&SL, P.size/4);

		// ---- Calculate time from here -----
		deWall(&P, &AFL, &SL, XAxis);
		// -----------------------------------

		write_simplex_list(argv[2], &SL);
	}
	exit(EXIT_SUCCESS);
}
