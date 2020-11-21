/********************************************
File name : dynamic_vector.c
Author : Omer Avioz
Reviewer : Liron Pollak
Infinity Labs OL95	
*******************************************/

/* 				External Libraries
-------------------------------------------*/
#include "dynamic_vector.h" /* dynamic_vector functions*/
#include <assert.h>	/*assert*/
#include <stdlib.h>	/* malloc, free, size_t */
#include <string.h>	/*memcpy*/


struct dynamic_vector
{
	void *vector;
	size_t num_of_elements;
	size_t capacity;
	size_t element_size;
};

/* 				Implementations
-------------------------------------------*/

vector_t *VectorCreate(size_t capacity, size_t element_size)
{
    vector_t *new_vector = NULL;
    
    assert ((0 < capacity) && (0 < element_size && 8 >= element_size));
    
    new_vector = (vector_t*)malloc(sizeof(vector_t));
    
    if( NULL == new_vector)
    {
        return NULL;
    }
    
    new_vector->vector = (void*) malloc ( capacity * element_size); 
    
    if(NULL == new_vector->vector)
    {
        return NULL;
    }
    
    new_vector->capacity = capacity;
    new_vector->element_size = element_size;
    new_vector->num_of_elements = (size_t)0;
    return new_vector;

}


void VectorDestroy(vector_t *dynamic_vector)
{
	assert(NULL != dynamic_vector);
	
	dynamic_vector->capacity = 0;
	dynamic_vector->element_size = 0;
	
	free (dynamic_vector->vector);
	dynamic_vector->vector = NULL;
	
	free (dynamic_vector);
}


void *VectorGetElement(const vector_t *dynamic_vector, size_t index)
{
	assert(NULL != dynamic_vector);
	
	return (void *)((char *)dynamic_vector->vector 
                            + index * dynamic_vector->element_size);
}


int VectorPopBack(vector_t *dynamic_vector)
{
	assert(NULL != dynamic_vector);
	
	if(dynamic_vector->num_of_elements == 0)
	{
		return 1;
	}

	if(((dynamic_vector->capacity) / (size_t)4) == (dynamic_vector->num_of_elements))
	{
	
		if(1 == VectorResize(dynamic_vector,(dynamic_vector->capacity / (size_t)2)))
		{
			return 1;
		}

	}
	
	dynamic_vector->num_of_elements -= (size_t)1;
	
	return 0;

}


int VectorPushBack(vector_t *dynamic_vector, const void *element)
{
	void *target = NULL;
	
	assert(NULL != dynamic_vector);
	assert(NULL != element);
	
	if((dynamic_vector->capacity) == (dynamic_vector->num_of_elements))
	{
		 	
		if(1 == VectorResize(dynamic_vector,(dynamic_vector->capacity * (size_t)2)))
		{
			return 1;
		}
		
	}
	target = (void *)((char *)dynamic_vector->vector 
                            + dynamic_vector->num_of_elements * dynamic_vector->element_size);
	memcpy(target, element,(dynamic_vector->element_size));
		
	 	   
	dynamic_vector->num_of_elements += (size_t)1;

	return 0;
	
}


size_t VectorSize(const vector_t *dynamic_vector)
{
	assert(NULL != dynamic_vector);
	
	return (dynamic_vector->num_of_elements);
}


size_t VectorCapacity(const vector_t *dynamic_vector)
{
	assert(NULL != dynamic_vector);
	
	return (dynamic_vector->capacity);
}


int VectorResize(vector_t *dynamic_vector, size_t new_size)
{
	assert(NULL != dynamic_vector);
	assert(0 < new_size);
	
	dynamic_vector->vector = (void *)realloc(dynamic_vector->vector, new_size * dynamic_vector->element_size);
	if(NULL == dynamic_vector->vector)
	{
		return 1;
	}
	else if(new_size < dynamic_vector->num_of_elements)
	{
		dynamic_vector->num_of_elements = new_size;	
	}
	dynamic_vector->capacity = new_size;
	return 0;
	
}

