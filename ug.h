typedef struct cell_struct {
	point *p;
	struct cell_struct *next;
} cell;

typedef struct {
	int sizeX;		
	int sizeY;	
  
   float grid_size;

   point min_point;
   point max_point;

   cell **c;		
} uniform_grid;

void bounding_box(point_set *P, uniform_grid *UG);
void gridSize(uniform_grid *UG, int size);
int createUniformGrid(point_set *P, uniform_grid *UG);
void print_uniform_grid(uniform_grid *UG);
