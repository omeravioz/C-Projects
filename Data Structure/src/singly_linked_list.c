/********************************************
File name : singly_linked_list.c
Author : Omer Avioz
Reviewer : Ayelet Canetti
Infinity Labs OL95	
*******************************************/

/* 				External Libraries
-------------------------------------------*/


#include <stddef.h> /* size_t */
#include <assert.h> /*assert */
#include <stdlib.h>	/*malloc, free */
#include "singly_linked_list.h"

struct node 
{
	void *data;
	node_t *next;
};

struct singly_linked_list
{
	node_t *begin;
	node_t *end;
};


slist_t *SListCreate(void)
{
	slist_t *new_slist = NULL;
	node_t *new_node = NULL;
	
	new_slist = (slist_t*)malloc(sizeof(slist_t));
	
	if(NULL == new_slist)
	{
		return NULL;
	} 
	
	new_node = (node_t*)malloc(sizeof(node_t));
	
	if(NULL == new_node)
	{
		free(new_slist);
		return NULL;
	}
	
	new_node->data = NULL;
	new_slist->end = new_node;
	new_slist->begin = new_slist->end;
	
	return new_slist;

}


 
void SListDestroy(slist_t *list)
{
	slist_iter_t current = NULL;
	slist_iter_t next = NULL;
	
	assert(NULL != list);
	
	current = list->begin;
	next = list->begin;
	

	if(SListIsEmpty(list))
	{
		free(list->end);	
		free(list);	
	}
	else
	{	
		while(current->next != list->end)
		{
			next = current->next;
			free(current);
			current = next;
		}
		
		free(next);
		free(list->end);	
		free(list);
		
	}
	
}


int SListPushBack(slist_t *list, const void *data)
{
	assert(NULL != list);
	assert(NULL != data);
	return SListInsertBefore(list, list->end, data);

}


void SListPopBack(slist_t *list)
{
	slist_iter_t current = NULL;
	
	assert(NULL != list);
	
	current = list->begin;
	
	while(current->next != list->end)
	{
		current = current->next;
	}
	SListRemove(list, current);
}


int SListInsertBefore(slist_t *list, slist_iter_t next_iterator, const void *data)
{
	node_t *new_node = NULL;

	assert(NULL != list);
	assert(NULL != next_iterator);	
	assert(NULL != data);
	
	new_node = (node_t*)malloc(sizeof(node_t));
	
	if(NULL == new_node)
	{
		return 1;
	}
	
    if (next_iterator == list->end)
    {
        list->end = new_node;
    }
	
	new_node->data = next_iterator->data;
	new_node->next = next_iterator->next;
	next_iterator->data = (void *)data;
	next_iterator->next = new_node;
		
	return 0;
}


void SListRemove(slist_t *list, slist_iter_t iterator)
{
	slist_iter_t next_iterator = NULL;
	
	assert(NULL != list);
	assert(NULL != iterator);	
	
	next_iterator = iterator->next;
	if(list->end == next_iterator)
	{
		list->end = iterator;
	}
	
	iterator->data = next_iterator->data;
	iterator->next = next_iterator->next;
	free(next_iterator);
}

 
slist_iter_t SListFindIter (const slist_t *list, const compare_t compare, const void *data)
{
	slist_iter_t current = NULL;
	
	assert(NULL != list);
	assert(NULL != compare);
	assert(NULL != data);
	
	current = list->begin;
	while(current != list->end)
	{
		if(compare((current->data), data) == 0)
		{
			return current;
		}
		current = current->next;
	}
	return current;	
}

 
int SListForEachIter(slist_iter_t first, slist_iter_t last, const action_function_t func,void *param)
{
	assert(NULL != first);
	assert(NULL != last);
	assert(NULL != func);
	assert(NULL != param);
	
	while(first != last)
	{
		if(func((first->data), param) != 0)
		{
			return 1;
		}
		first = first->next;
	}
	return 0;	
}


size_t SListSize(const slist_t *list)
{
	slist_iter_t current = NULL;
	size_t count = 0;
	
	assert(NULL != list);
	
	current = list->begin;
	while(current != list->end)
	{

		++count;
		current = current->next;
	}
	return count;
}

 
slist_iter_t SListBegin(const slist_t *list)
{
	assert(NULL != list);
	
	return (list->begin);
}


 
slist_iter_t SListEnd(const slist_t *list)
{
	assert(NULL != list);
	
	return (list->end);
}


slist_iter_t SListNextIter(slist_iter_t iterator)
{
	assert(NULL != iterator);
	
	return (iterator->next);
}



void *SListGetData(slist_iter_t iterator)
{
	assert(NULL != iterator);
	
	return (iterator->data);
}



int SListIsEmpty(const slist_t *list)
{
	assert(NULL != list);
	
	return ( (list->end) == (list->begin));
}


int SListIsSameIter(slist_iter_t iterator1, slist_iter_t iterator2)
{
	assert(NULL != iterator1);
	assert(NULL != iterator2);
	
	return (iterator1 == iterator2);
}

void SListAppend(slist_t *src, slist_t *dest)
{
	dest->end->data = src->begin->data;
	dest->end->next = src->begin->next;
	
	src->begin->data = NULL;
	src->begin->next = NULL;
	
	dest->end = src->end;
	src->end = src->begin;
	
}
