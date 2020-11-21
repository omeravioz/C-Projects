/********************************************
File name : sorted_list.c
Author : Omer Avioz
Reviewer : Eliran Farag
Infinity Labs OL95	
*******************************************/

/* 				External Libraries
-------------------------------------------*/

#include <assert.h>	/*assert*/
#include <stdlib.h>	/* malloc, free, size_t */

#include "sorted_list.h" /* sorted_list API*/


struct sorted_list 
{
	dlist_t *sorted_list;
	compare_t compare;
};

sorted_list_t *SortedListCreate(compare_t compare)
{
	sorted_list_t *new_list = (sorted_list_t *) malloc (sizeof(sorted_list_t));
	
	assert(NULL != compare);
	
	if(NULL == new_list)
	{
		return NULL;
	}
	
	new_list->sorted_list = DListCreate();
	
	if(NULL == new_list->sorted_list)
	{
		free(new_list);
		return NULL;
	}
	
	new_list->compare = compare;
	return new_list;
}

void SortedListDestroy(sorted_list_t *list)
{
	assert(NULL != list);
	
	DListDestroy(list->sorted_list);
	free(list); list = NULL;
}


void SortedListPopBack(sorted_list_t *list)
{
	assert(NULL != list);
	
	DListPopBack(list->sorted_list);
}

sorted_list_iter_t SortedListInsert(sorted_list_t *list, const void *data)
{
	sorted_list_iter_t iterator = {NULL};
	
	assert(NULL != list);
	assert(NULL != data);
	
	iterator = SortedListBegin(list);	
	while(SortedListIsSameIter(iterator, SortedListEnd(list)) != 1)
	{
		
		if(list->compare(data, SortedListGetData(iterator)) <= 0)
		{
			iterator.sorted_iter = DListInsert(list->sorted_list, iterator.sorted_iter, data);
			return iterator;
		}
		
		iterator = SortedListNextIter(iterator);
	}
	iterator.sorted_iter = DListInsert(list->sorted_list, iterator.sorted_iter, data);
	
	return iterator;
	
}

sorted_list_iter_t SortedListRemove(sorted_list_t *list, sorted_list_iter_t iterator)
{
	sorted_list_iter_t next_iterator = {NULL};

	#ifndef NDEBUG
    next_iterator.list_owner = list; 
	#endif
	
	assert(NULL != list);
	assert(NULL != iterator.sorted_iter.internal);
	
	next_iterator.sorted_iter = DListRemove(list->sorted_list, iterator.sorted_iter);
	return 	next_iterator;
	
}

sorted_list_iter_t SortedListFind(sorted_list_t *list, const void *data)
{
	sorted_list_iter_t iterator = {NULL};
	
	assert(NULL != list);
	assert(NULL != data);
	
	iterator = SortedListBegin(list);	
	while(SortedListIsSameIter(iterator, SortedListEnd(list)) != 1)
	{
		
		if(list->compare(data, SortedListGetData(iterator)) == 0)
		{
			return iterator;
		}
		
		iterator = SortedListNextIter(iterator);
	}
	
	return iterator;
	
}

sorted_list_iter_t SortedListFindIf(sorted_list_t *list, is_match_t is_match, const void *data)
{
	sorted_list_iter_t find_iterator = {NULL};
	
	assert(NULL != list);
	assert(NULL != is_match);
	assert(NULL != data);
	
	find_iterator.sorted_iter = DListFind(SortedListBegin(list).sorted_iter,
										  SortedListEnd(list).sorted_iter,
										  is_match,
										  data);
	
	#ifndef NDEBUG
    find_iterator.list_owner = list; 
	#endif
	
	return find_iterator;
	
}

int SortedListForEach(sorted_list_iter_t from, sorted_list_iter_t to, action_t func, void *param)
{
	assert(NULL != from.sorted_iter.internal);
	assert(NULL != to.sorted_iter.internal);
	assert(NULL != func);
	assert(NULL != param);
	assert(from.list_owner == to.list_owner);

	return DListForEach(from.sorted_iter, to.sorted_iter, func, param);
	
}

size_t SortedListSize(const sorted_list_t *list)
{
	assert(NULL != list);
	
	return DListSize(list->sorted_list);
	
}

sorted_list_iter_t SortedListBegin(const sorted_list_t *list)
{
	sorted_list_iter_t begin_iterator = {NULL};
	
	assert(NULL != list);
	
	begin_iterator.sorted_iter = DListBegin(list->sorted_list);
	
	#ifndef NDEBUG
    begin_iterator.list_owner = (sorted_list_t *)list; 
	#endif
	
	return begin_iterator;
}

sorted_list_iter_t SortedListEnd(const sorted_list_t *list)
{
	sorted_list_iter_t end_iterator = {NULL};
	
	assert(NULL != list);
	
	end_iterator.sorted_iter = DListEnd(list->sorted_list);
	
	#ifndef NDEBUG
    end_iterator.list_owner = (sorted_list_t *)list; 
	#endif
	
	return end_iterator;
	
}

sorted_list_iter_t SortedListNextIter(sorted_list_iter_t iterator)
{
	sorted_list_iter_t next_iterator = {NULL};

	#ifndef NDEBUG
    next_iterator.list_owner = iterator.list_owner;
	#endif
	
	assert(NULL != iterator.sorted_iter.internal);

	next_iterator.sorted_iter = DListNextIter(iterator.sorted_iter);
	

	
	return next_iterator;
	
}

sorted_list_iter_t SortedListPrevIter(sorted_list_iter_t iterator)
{
	sorted_list_iter_t prev_iterator = {NULL};

	#ifndef NDEBUG
    prev_iterator.list_owner = iterator.list_owner;
	#endif
	
	assert(NULL != iterator.sorted_iter.internal);

	prev_iterator.sorted_iter = DListPrevIter(iterator.sorted_iter);
	

	
	return prev_iterator;
		
}

void *SortedListGetData(sorted_list_iter_t iterator)
{
	assert(NULL != iterator.sorted_iter.internal);
	
	return DListGetData(iterator.sorted_iter);
	
}

int SortedListIsEmpty(const sorted_list_t *list)
{
	assert(NULL != list);
	
	return DListIsEmpty(list->sorted_list);
	
}

int SortedListIsSameIter(sorted_list_iter_t iterator1, sorted_list_iter_t iterator2)
{
	assert(iterator1.list_owner == iterator2.list_owner);
	
	return DListIsSameIter(iterator1.sorted_iter, iterator2.sorted_iter);
	
}

void SortedListMerge(sorted_list_t *dest_list, sorted_list_t *src_list)
{
	sorted_list_iter_t dest_iter = {NULL};
	sorted_list_iter_t src_iter = {NULL};
	
	assert(NULL != dest_list);
	assert(NULL != src_list);
	
	dest_iter = SortedListBegin(dest_list);
	src_iter = SortedListBegin(src_list);
	
	while(SortedListIsEmpty(src_list) == 0)
	{
		
		if(SortedListIsSameIter(SortedListEnd(dest_list), dest_iter))
		{
			DListSplice(dest_iter.sorted_iter, src_iter.sorted_iter, 			                					   	SortedListEnd(src_list).sorted_iter);	
				
		}
		
		else if(dest_list->compare(SortedListGetData(src_iter),
								   SortedListGetData(dest_iter)) <= 0)
		{
			src_iter = 	SortedListNextIter(src_iter);
		 	DListSplice(dest_iter.sorted_iter, SortedListPrevIter(src_iter).sorted_iter,
					    src_iter.sorted_iter );

		}
		
		else
		{
			dest_iter = SortedListNextIter(dest_iter);		
		}
	}
}







