/********************************************
File name : queue.c
Author : Omer Avioz
Reviewer : Mor Espresco
Infinity Labs OL95	
*******************************************/

/* 				External Libraries
-------------------------------------------*/
#include <assert.h> /*assert */
#include <stdlib.h>	/*malloc, free */
#include "singly_linked_list.h"
#include "queue.h"

struct queue
{
	slist_t *slist;
};

queue_t *QueueCreate(void);
void QueueDestroy(queue_t *queue);
int QueueEnqueue(queue_t *queue, const void *data);
void QueueDequeue(queue_t *queue);
size_t QueueSize(const queue_t *queue);
void *QueuePeek(const queue_t *queue);
int QueueIsEmpty(const queue_t *queue);
void QueueAppend(queue_t *src, queue_t *dest);



queue_t *QueueCreate(void)
{
	queue_t *new_queue = (queue_t*) malloc (sizeof(queue_t));
	
	if(NULL == new_queue)
	{
		return NULL;
	}
	
	new_queue->slist = SListCreate();
	
	if(NULL == new_queue->slist)
	{
		free(new_queue);
		return NULL;
	}
	return new_queue;
}

void QueueDestroy(queue_t *queue)
{
	assert(NULL != queue);
	
	SListDestroy(queue->slist);
	free(queue); queue = NULL;
	
}

int QueueEnqueue(queue_t *queue, const void *data)
{
	assert(NULL != queue);
	assert(NULL != data);
	
	return SListPushBack((queue->slist),data);
	
}

void QueueDequeue(queue_t *queue)
{
	assert(NULL != queue);
	
	SListRemove(queue->slist, SListBegin(queue->slist));
}

size_t QueueSize(const queue_t *queue)
{
	assert(NULL != queue);
	
	return SListSize(queue->slist);
}

void *QueuePeek(const queue_t *queue)
{
	assert(NULL != queue);
	
	return (void *)SListGetData(SListBegin(queue->slist));
}

int QueueIsEmpty(const queue_t *queue)
{
	assert(NULL != queue);
	
	return SListIsEmpty(queue->slist);
}

void QueueAppend(queue_t *src, queue_t *dest)
{
	assert(NULL != src);
	assert(NULL != dest);
	
	SListAppend(src->slist, dest->slist);
}

