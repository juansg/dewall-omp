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

typedef struct {
  int x;
  int y;
} cell_index;

void bounding_box(point_set *P, uniform_grid *UG);
void gridSize(uniform_grid *UG, int size);
int createUniformGrid(point_set *P, uniform_grid *UG);
void print_uniform_grid(uniform_grid *UG);

void calc_full_box(face *f, uniform_grid *UG, cell_index *start, 
    cell_index *end, cell_index *dir);
int in_halfspace(int x, int y, face *f, uniform_grid *UG);
int scan_full_box(face *f, uniform_grid *UG, cell_index *start, cell_index *end, 
    cell_index *dir, point **p, float *min_rad);

float calc_box(face *f, uniform_grid *UG, cell_index *start, cell_index *end, float radius);
float scan_box(face *f, uniform_grid *UG, cell_index *start, cell_index *end, 
    point **p, float *min_rad);
