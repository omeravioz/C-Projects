/********************************************
File name : cbuff_test.c
Author : Omer Avioz
Reviewer : Ron Benyamin
Infinity Labs OL95	
*******************************************/

/* 				External Libraries
-------------------------------------------*/

#include <stdlib.h>	/*malloc, free*/
#include <assert.h>	/*assert*/
#include "cbuff.h"	/*Circular beffer functions*/

#define INDEX_OF_ELEMENT(element, capacity) (element % capacity)

struct circular_buffer
{
	size_t read;
	size_t write;
	size_t capacity;
	char data[1];
};

static int CBuffIsFull(const c_buff_t *cbuff)
{
	assert(NULL != cbuff);
	
	return ((cbuff->write - cbuff->read) == cbuff->capacity);
	
}

static void CircularIndexsReset(c_buff_t *cbuff)
{
	assert(NULL != cbuff);
	
	if(cbuff->write > cbuff->capacity && cbuff->read > cbuff->capacity)
	{
		cbuff->read -= cbuff->capacity;
        cbuff->write -= cbuff->capacity;
	}
	
}

int CBuffIsEmpty(const c_buff_t *cbuff)
{
	assert(NULL != cbuff);
	
	return(cbuff->write == cbuff->read);
	
}

c_buff_t *CBuffCreate(size_t capacity)
{
	c_buff_t *new_buff = (c_buff_t *)malloc(sizeof(c_buff_t) + capacity);
	if(NULL == new_buff)
	{
		return NULL;
	}
	
	new_buff->read = 0UL;
	new_buff->write = 0UL;
	new_buff-> capacity = capacity;
	return new_buff;
	
}

void CBuffDestroy(c_buff_t *cbuff)
{
	assert(NULL != cbuff);
	
	free(cbuff);
	cbuff = NULL;
}

size_t CBuffRead(c_buff_t *cbuff, void *dest, size_t count)
{	
	size_t num_of_copied_bytes = 0UL;
	
	assert(NULL != cbuff);
	assert(NULL != dest);
	
	while((num_of_copied_bytes < count) && (CBuffIsEmpty(cbuff) == 0))
	{
		*(char *)dest = cbuff->data[INDEX_OF_ELEMENT(cbuff->read,cbuff->capacity)];
		++(cbuff->read);
		dest =(char *)dest + 1;
		++num_of_copied_bytes;
	}
	
 	CircularIndexsReset(cbuff);
	
	return num_of_copied_bytes;

}

size_t CBuffWrite(c_buff_t *cbuff, void *src, size_t count)
{
	size_t num_of_copied_bytes = 0UL;
	
	assert(NULL != cbuff);
	assert(NULL != src);
	
	while((num_of_copied_bytes < count) && CBuffIsFull(cbuff) == 0)
	{
		cbuff->data[INDEX_OF_ELEMENT(cbuff->write,cbuff->capacity)] = *(char *)src;
		++(cbuff->write);
		src = (char *)src + 1;
		++num_of_copied_bytes;
	}
	
	return num_of_copied_bytes;
	
}


size_t CBuffFreeSpace(const c_buff_t *cbuff)
{
	assert(NULL != cbuff);
	
	return (cbuff->capacity - (cbuff->write - cbuff->read));
	
}

size_t CBuffCapacity(const c_buff_t *cbuff)
{
	assert(NULL != cbuff);
	
	return cbuff->capacity;
	
}


