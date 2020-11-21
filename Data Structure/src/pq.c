	/******************************************************************************
 * Title:		pq.c
 * Description:	Implementations of pq functions
 * Author:		Omer Avioz
 * Reviewer:	Ayelet Canetti	
 * 
 * InfinityLabs OL95
 *****************************************************************************/
#include <assert.h> /* assert() */  
#include <stdlib.h> /* malloc(), free() */
#include "pq.h" /* pq functions declaration */
#include "sorted_list.h" /* sl functions declaration */

/**********************************pq************************************/

struct pq
{
	sorted_list_t *sorted_list;
};

/*******************************************************************************
                            PQCreate                             
*******************************************************************************/
pq_t *PQCreate(int (*cmp)( const void *new_data, const void *existing_data))
{
	pq_t *pq = (pq_t *) malloc (sizeof(pq_t));
	
	assert(NULL != cmp);
	
	if(NULL == pq)
	{
		return NULL;
	}
	
	pq->sorted_list = SortedListCreate(cmp);
	
	if(NULL == pq->sorted_list)
	{
		free(pq);
		return NULL;
	}

	return pq;
}

/*******************************************************************************
                             PQDestroy                              
*******************************************************************************/
void PQDestroy(pq_t *pq)
{
	assert(NULL != pq);
	SortedListDestroy(pq->sorted_list);
	free(pq); pq = NULL;
	
}

/*******************************************************************************
                             PQEnqueue                            
*******************************************************************************/
int PQEnqueue(pq_t *pq, const void *data)
{
	sorted_list_iter_t iter = {NULL};
	
	assert(NULL != pq);
	assert(NULL != data);
	
	iter = SortedListInsert(pq->sorted_list, data);
	return SortedListIsSameIter(iter, SortedListEnd(pq->sorted_list));	
		
}


/*******************************************************************************
                             PQDequeue                               
*******************************************************************************/
void *PQDequeue(pq_t *pq)
{
	void *last_element = NULL;
	
	assert(NULL != pq);
	
	last_element = PQPeek(pq);
	SortedListRemove(pq->sorted_list, SortedListPrevIter(SortedListEnd(pq->sorted_list)));
	
	return last_element;
	
}


/*******************************************************************************
                             PQSize                           
*******************************************************************************/
size_t PQSize(const pq_t *pq)
{
	assert(NULL != pq);
	
	return SortedListSize(pq->sorted_list);
	
}


/*******************************************************************************
                             PQPeek                            
*******************************************************************************/

void *PQPeek(const pq_t *pq)
{
	assert(NULL != pq);
	
	return SortedListGetData(SortedListPrevIter(SortedListEnd(pq->sorted_list)));
	
}

/*******************************************************************************
                             PQIsEmpty                              
*******************************************************************************/
int PQIsEmpty(const pq_t *pq)
{
	assert(NULL != pq);
	
	return 	SortedListIsEmpty(pq->sorted_list);

}

/*******************************************************************************
                             PQErase                            
*******************************************************************************/
void *PQErase(pq_t *pq, int (*is_match)(const void *data, const void *params), void *params)
{
	sorted_list_iter_t iter = {NULL};
	void *data = NULL;
	
	assert(NULL != pq);
	assert(NULL != is_match);
	assert(NULL != params);
	
	iter = SortedListFindIf(pq->sorted_list, is_match, params);
	if(0 == SortedListIsSameIter(iter, SortedListEnd(pq->sorted_list)))	
	{
		data = SortedListGetData(iter);
		SortedListRemove(pq->sorted_list, iter);
	}
	
	return data;
}

/*******************************************************************************
                            PQClear                        
*******************************************************************************/
void PQClear(pq_t *pq)
{
	sorted_list_iter_t iter = {NULL};
	
	assert(NULL != pq);
	
	iter = SortedListBegin(pq->sorted_list);
	while(0 == SortedListIsSameIter(iter,SortedListEnd(pq->sorted_list)))
	{
		iter = SortedListRemove(pq->sorted_list ,iter);
	}
	
}

