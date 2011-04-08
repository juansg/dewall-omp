typedef void * pointer;

typedef struct l_elem {
  struct l_elem *next;
  struct l_elem *prev;
  pointer obj;
} list_element;

typedef struct h_element {
  struct h_element *next;
  struct h_element *prev;
  list_element *list_elem;
} hash_element;

typedef struct {
  hash_element **hash_elem;
  int size;
  int (*hash_key)(pointer);
} hash;

typedef struct {
  list_element *first;
  list_element *last;
  list_element *current;
  int size_obj;
  int size;
  int (*equal_obj)(void *, void *);
  hash *hash_list;
} list;


void initialize_list(list *l, int obj_size,
    int (* eq)(void *elem1, void *elem2));	
void hash_list(list *l, int size, int (*hash_key)(void *));
int equal(list *l, pointer elem1, pointer elem2);


int insert_list(list *l, pointer object) ;
int insert_hash(hash *hl, list_element *elem);

int extract_list(list *l, pointer obj);
int delete_hash(list *l, pointer object);   

int member_list(list *l, pointer object);
int member_hash(list *l, pointer object);	

int delete_current_list(list *l);
int delete_list(list *l, pointer object);
