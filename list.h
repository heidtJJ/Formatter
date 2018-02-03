#ifndef LIST_H
#define LIST_H

// linked list type
typedef struct list_s {
	char* buffer;
	int size;
	struct list_s *prev;
	struct list_s *next;
	
}
list_t;

// constructor
list_t *make_list(char*);
list_t *free_node(list_t* head);
void freeList(list_t* head);

#endif
