/********************************************
File name : stack.c
Author : Omer Avioz
Reviewer : Dafna Kadosh Mahler
Infinity Labs OL95	
*******************************************/

/* 				External Libraries
-------------------------------------------*/
#include "stack.h"
#include <stddef.h> /* size_t */
#include <string.h> /*memcpy */
#include <assert.h> /*assert */
#include <stdlib.h>	/*malloc */
#include <stdio.h>  /*printf */



struct stack
{
	void *array;
	void *current;
	size_t element_size;
	size_t capacity;
};

/*			Functions Implementations
------------------------------------------*/

size_t StackSize(const stack_t *stack)
{
	assert( NULL != stack);

	return (((size_t)(stack->current) - (size_t)(stack->array))/(stack->element_size));
}

int StackIsEmpty(const stack_t *stack)
{
	assert( NULL != stack);
	
	return StackSize(stack) == 0;
}


stack_t *StackCreate(size_t capacity, size_t element_size)
{

    stack_t *new_stack = NULL;
    
    assert(0 < capacity);
    assert(0 < element_size);
    
    new_stack = (stack_t*) malloc (sizeof(stack_t));
    if( NULL == new_stack)
    {
        return NULL;
    }
    
    new_stack->array = (void*) malloc ( capacity * element_size); 
    
    if(new_stack->array == NULL)
    {
    	free(new_stack);
        return NULL;
    }
    
    new_stack->current = new_stack->array;
    new_stack->capacity = capacity;
    new_stack->element_size = element_size;
    return new_stack;
}


void StackDestroy(stack_t *stack)
{
	assert(NULL != stack);
	
	stack->capacity = 0;
	stack->element_size = 0;
	
	free (stack->array);
	stack->current = NULL;
	stack->array = NULL;
	
	free (stack);
	stack = NULL;
}


void StackPush(stack_t *stack, const void *data)
{
	assert(NULL != stack);
	assert(NULL != data);
	
	if (StackSize(stack) < (stack->capacity))
    {
        memcpy((stack -> current), data, (stack -> element_size));
        (stack->current) = (void*)((size_t)(stack->current) + (stack->element_size));
        
    }

}

void StackPop(stack_t *stack)
{
	assert(NULL != stack);
	assert(NULL != stack->current);
	
	stack->current = ((void*)((size_t)(stack->current) - (stack->element_size)));	
}

void *StackPeek(const stack_t *stack)
{
	assert(NULL != stack);
	assert(NULL != stack->current);
	
	if(0 == StackIsEmpty(stack))
	{
		return ((void*)((size_t)(stack->current) - (stack->element_size)));
	}
	
	else
	{
		return NULL;
	}
}

size_t StackCapacity(const stack_t *stack)
{
	assert(NULL != stack);
	
	return (stack->capacity);
}









