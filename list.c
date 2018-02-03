#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

list_t *make_list(char* buffer)
{
	list_t *ptr;

	ptr = (list_t *)malloc(sizeof(list_t));
	assert( ptr != NULL );
	ptr->buffer = buffer;
	ptr->prev = NULL;
	ptr->next = NULL;

	return ptr;
}

list_t *free_node(list_t* cur){
   list_t* tmp;
   if(cur != NULL)
    {
       tmp = cur;
       cur = cur->next;
       free(tmp);
    }
    return cur;
}

void freeList(list_t* head)
{
   list_t* tmp;

   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }
}
