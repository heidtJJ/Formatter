#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

list_t *make_list( char* ch )
{
	list_t *ptr;

	ptr = (list_t *)malloc(sizeof(list_t));
	assert( ptr != NULL );
	ptr->c = ch;
	ptr->prev = NULL;
	ptr->next = NULL;

	return ptr;
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
