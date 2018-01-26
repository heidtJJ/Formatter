#ifndef LIST_H
#define LIST_H

// linked list type
typedef struct list_s {
	char* c;
	struct list_s *prev;
	struct list_s *next;
}
list_t;

// constructor
list_t *make_list( char* );
void freeList(list_t* head);
#endif
