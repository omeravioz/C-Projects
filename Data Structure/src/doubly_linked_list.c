/********************************************
File name : doubly_linked_list.c
Author : Omer Avioz
Reviewer : Ayelet Canetti
Infinity Labs OL95	
*******************************************/

/* 				External Libraries
-------------------------------------------*/

#include <assert.h>	/*assert*/
#include <stdlib.h>	/* malloc, free, size_t */
#include "doubly_linked_list.h" /* doubly_linked_list functions*/

struct node 
{
	void *data;
	node_t *next;
	node_t *prev;
};

struct doubly_linked_list 
{
	node_t head;
	node_t tail;
	
};


dlist_t *DListCreate(void)
{

	dlist_t *new_dlist = (dlist_t*)malloc(sizeof(dlist_t));
	
	if(NULL == new_dlist)
	{
		return NULL;
	}
	
	(new_dlist->head).data = NULL;
	(new_dlist->tail).data = NULL;
	(new_dlist->head).next = &(new_dlist->tail);
	(new_dlist->tail).prev = &(new_dlist->head);
	
	return new_dlist;	
	 
}

void DListDestroy(dlist_t *list)
{
	
	assert(NULL != list);
	
	while(0 == DListIsEmpty(list))
	{
		DListRemove(list, DListBegin(list));
	}
	
	free(list);

}

dlist_iter_t DListPushBack(dlist_t *list, const void *data)
{
	dlist_iter_t new_iter = {NULL};
	
	assert(NULL != list);
	assert(NULL != data);
	
	new_iter.internal = &(list->tail);
	
	return DListInsert(list, new_iter, data);
	
}

void DListPopBack(dlist_t *list)
{
	dlist_iter_t iter_to_remove = {NULL};
	
	assert(NULL != list);
	
	iter_to_remove.internal = (list->tail).prev;
	DListRemove(list, iter_to_remove);
	
}

dlist_iter_t DListInsert(dlist_t *list, dlist_iter_t next_iterator, const void *data)
{
	node_t *new_node = NULL;
	dlist_iter_t new_iter = {NULL};
	
	assert(NULL != list);
	assert(NULL != next_iterator.internal);
	assert(NULL != data);
	
	new_node = (node_t*)malloc(sizeof(node_t));
	
	if(NULL == new_node)
	{
		return DListEnd(list);
	}
	
	new_node->data = (void *)data;
	new_node->prev = (next_iterator.internal)->prev;
	new_node->next = next_iterator.internal;
	new_iter.internal = new_node;
	
	((next_iterator.internal)->prev)->next = new_node;
	(next_iterator.internal->prev) = new_node;
	
	return new_iter;
		 
}

dlist_iter_t DListRemove(dlist_t *list, dlist_iter_t iterator)
{
	dlist_iter_t next_iterator = {NULL};
	
	assert(NULL != list);
	assert(NULL != iterator.internal);
	
	next_iterator.internal = iterator.internal->next;
	(iterator.internal->next)->prev = iterator.internal->prev;
	(iterator.internal->prev)->next = iterator.internal->next;
	
	free(iterator.internal);
	return next_iterator;
	
}

dlist_iter_t DListFind(dlist_iter_t from, dlist_iter_t to, is_match_t is_match, const void *data)
{
	
	assert(NULL != from.internal);
	assert(NULL != to.internal);
	assert(NULL != is_match);
	assert(NULL != data);
	

	while(from.internal != to.internal)
	{
		if(is_match(from.internal->data, data))
		{
			return from;
		}
		from.internal = from.internal->next;
	}
	return to;	
	
}

int DListForEach(dlist_iter_t from, dlist_iter_t to, action_t func, void *param)
{
	assert(NULL != from.internal);
	assert(NULL != to.internal);
	assert(NULL != func);
	
	while(from.internal != to.internal)
	{
		if(func((from.internal->data), param) != 0)
		{
			return 1;
		}
		from.internal = from.internal->next;
	}
	return 0;	
	
}

size_t DListSize(const dlist_t *list)
{
	node_t *current = NULL;
	size_t count = 0;
	
	assert(NULL != list);
	
	current = (list->head.next);
	while(current != &(list->tail))
	{
		++count;
		current = current->next;
	}
	return count;	
	
}

dlist_iter_t DListBegin(const dlist_t *list)
{
	dlist_iter_t begin_iterator = {NULL};
	
	assert(NULL != list);
	
	begin_iterator.internal = (node_t *)(list->head.next);
	return begin_iterator;
	
}

dlist_iter_t DListEnd(const dlist_t *list)
{
	dlist_iter_t end_iterator = {NULL};
	
	assert(NULL != list);
	
	end_iterator.internal = (node_t *)(&(list->tail));
	return end_iterator;
	
}

dlist_iter_t DListNextIter(dlist_iter_t iterator)
{
	dlist_iter_t next_iterator = {NULL};

	assert(NULL != iterator.internal);
	
	next_iterator.internal = iterator.internal->next;
	return next_iterator;
	
}

dlist_iter_t DListPrevIter(dlist_iter_t iterator)
{
	dlist_iter_t prev_iterator = {NULL};

	assert(NULL != iterator.internal);
	
	prev_iterator.internal = (iterator.internal)->prev;
	return prev_iterator;
	
}

void *DListGetData(dlist_iter_t iterator)
{
	assert(NULL != iterator.internal);
	return (iterator.internal)->data;
	
}

int DListIsEmpty(const dlist_t *list)
{
	assert(NULL != list);
	return(list->head.next == &(list->tail));	
	
}

int DListIsSameIter(dlist_iter_t iterator1, dlist_iter_t iterator2)
{
	assert(NULL != iterator1.internal);
	assert(NULL != iterator2.internal);
	
	return((iterator1.internal) == (iterator2.internal));
	
}

dlist_iter_t DListSplice(dlist_iter_t dest_iter, dlist_iter_t from, dlist_iter_t to)
{
	dlist_iter_t prev_from = {NULL};
	assert(NULL != from.internal);
	assert(NULL != dest_iter.internal);
	
	prev_from.internal = (from.internal)->prev;
	
	((from.internal)->prev)->next = to.internal;
	
	(from.internal)->prev = (dest_iter.internal)->prev;
	((dest_iter.internal)->prev)->next = from.internal;
	
	(to.internal->prev)->next = (dest_iter.internal);
	(dest_iter.internal)->prev = (to.internal)->prev;
	
	(to.internal)->prev = prev_from.internal;
	return dest_iter;
	
}

int DListMultiFind(dlist_iter_t from, dlist_iter_t to, is_match_t is_match, 
                                       const void *data, dlist_t *output_list)
{
	
	assert(NULL != from.internal);
	assert(NULL != to.internal);
	assert(NULL != is_match);
	assert(NULL != data);
	
	while(DListIsSameIter(from, to) == 0)
	{
		if(is_match((from.internal->data), data))
		{
			if(DListIsSameIter((DListPushBack(output_list, from.internal->data)), DListEnd(output_list)))
			{
				return 1;
			}
		}
		
		from.internal = (from.internal)->next;
	}
	
	return 0;
	
}


