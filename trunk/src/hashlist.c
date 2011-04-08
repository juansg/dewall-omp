#include <stdio.h>
#include <stdlib.h>
#include "hashlist.h"

//Debug trick
#define LOGGER printf("[%s - %s] : file %s, line %d\n", __DATE__, __TIME__, __FILE__,__LINE__)

void initialize_list(list *l, int obj_size,
    int (* eq)(void *elem1, void *elem2)) {
  if (l){
    l->first = NULL;
    l->last = NULL;
    l->current = NULL;

    l->size = 0;
    l->size_obj = obj_size;

    l->equal_obj = eq;
    l->hash_list = NULL;
  }
}

void hash_list(list *l, int size, int (*hash_key)(void *)) {
  hash *h_list;
  if (size < 5)
    return;
  if(!l->hash_list) {	    
    // Not deallocated: created once and always needed during the algorithm's execution
    h_list = (hash *)malloc(sizeof(hash));
    if (h_list) {
      h_list->size = size;
      h_list->hash_key = hash_key;
      // Not deallocated: created once and always needed during the algorithm's execution
      h_list->hash_elem = (hash_element **)calloc(size,sizeof(hash_element *));		
      if(h_list->hash_elem)
        l->hash_list = h_list;
      else 
        // Allocated (here) in hash_list
        free(h_list);
    }
  }
}

int equal(list *l, pointer elem1, pointer elem2) {
  if(l->equal_obj) return l->equal_obj(elem1,elem2);
  return 0;
}


int insert_list(list *l, pointer object) {
  list_element *elem;
  list_element *old_elem;

  // Dealocated in extract_list or delete_current_list
  elem = (list_element *)malloc(sizeof(list_element));
  if(!elem)
    return 0;
  elem->obj = object;

  if(l->hash_list) 
    insert_hash(l->hash_list, elem);

  old_elem = l->last;
  l->last = elem;
  l->last->next = NULL;
  l->last->prev = old_elem;
  if(!old_elem) // first element inserted
    l->first = elem;
  else 
    old_elem->next = elem;

  l->size++;
  return 1;
}


int extract_list(list *l, pointer obj) {
  list_element *elemtofree;
  pointer *object = (pointer *)obj;

  if(l->size < 1 || !(l->first)) 
    return 0;	               

  *object = l->first->obj;         
  elemtofree = l->first;
  l->first = l->first->next;
  if(l->first) 
    l->first->prev = NULL; 
  else l->last = NULL;        

  l->size--;

  if(l->hash_list) 
    return delete_hash(l, *object);   

  return 1;
}

int member_list(list *l, pointer object) {
  list_element *temp_current = l->current;
  if(l->hash_list)
    return member_hash(l, object);	

  l->current = l->first;
  int i = 0;
  for(i = 0; i < l->size && l->current; i++) { 	
    if(equal(l, object, l->current->obj)) {
      return 1;			      
    }
    l->current = l->current->next;
  }			
  l->current = temp_current;
  return 0;
}

int delete_current_list(list *l) {

  if(l->size_obj == 0 || !l->current)
    return 0;

  if(l->hash_list)
    delete_hash(l, l->current->obj);

  if(l->first == l->current) 
    l->first = l->current->next;

  if(l->last == l->current)
    l->last = l->current->prev;

  if(l->current->next)
    l->current->next->prev = l->current->prev;

  if(l->current->prev)
    l->current->prev->next = l->current->next;	

  // Allocated in insert_list 
  free(l->current);
  l->current = NULL;
  l->size--;

  if (l->size_obj == 0)
    l->first = l->last = NULL;	
  return 1;	
}

int delete_list(list *l, pointer object) {
  int result = 0;
  list_element *current = l->current;
  list_element *current_next = NULL;

  if(l->current) 
    current_next = l->current->next;

  if(member_list(l, object)) 
    result = delete_current_list(l);
  else result = 0;

  if(current_next != l->current) 
    l->current = current;

  return result;
}

int insert_hash(hash *hl, list_element *elem) {
  hash_element *h_elem;	
  long ind = abs(hl->hash_key(elem->obj));	
  ind = ind % (hl->size);

  // Deallocated in delete_hash
  h_elem = (hash_element *)malloc(sizeof(hash_element));
  if(!h_elem) 
    return 0;

  h_elem->list_elem = elem;
  h_elem->next = hl->hash_elem[ind];
  h_elem->prev = NULL;


  if (hl->hash_elem[ind]) 
    hl->hash_elem[ind]->prev = h_elem;	
  hl->hash_elem[ind] = h_elem;

  return 1;	
}



int member_hash(list *l, pointer obj) {
  list_element *elem;
  hash_element *h_elem;
  long ind;

  if(!l->hash_list)
    return 0;

  ind = abs(l->hash_list->hash_key(obj));
  ind = ind % (l->hash_list->size);
  h_elem = l->hash_list->hash_elem[ind];

  while(h_elem) {
    elem = h_elem->list_elem;
    if(equal(l, obj, elem->obj)){
      l->current = elem;
      return 1;
    }
    h_elem = h_elem->next;
  }	
  return 0;
}

int delete_hash(list *l, pointer obj) {
  list_element *elem;
  hash_element *h_elem;
  long ind;

  if(!l->hash_list)
    return 0;

  ind = abs(l->hash_list->hash_key(obj));
  ind = ind % (l->hash_list->size);
  h_elem = l->hash_list->hash_elem[ind];

  while(h_elem) {
    elem = h_elem->list_elem;
    if(equal(l, obj, elem->obj)){
      if(h_elem->prev) 
        (h_elem->prev)->next = h_elem->next;
      else 
        l->hash_list->hash_elem[ind] = h_elem->next;
      if(h_elem->next) 
        (h_elem->next)->prev = h_elem->prev;
      // Allocated in insert_hash
      free(h_elem);
      return 1;
    }
    h_elem = h_elem->next;
  }	
  return 0;
}
