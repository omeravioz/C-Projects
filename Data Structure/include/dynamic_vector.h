/***************************************************************************************************
*                             DS - DYNAMIC VECTOR - HEADER FILE        
* 												 		 
* Description: API of dynamic vector functions.
* Worksheet: 3											 
* Date: 29.09.2020										 
* InfinityLabs OL95										 
***************************************************************************************************/

/*--------------------------------- Header Guard -------------------------------------------------*/

#ifndef __ILRD_OL95_DYNAMICVECTOR_H__
#define __ILRD_OL95_DYNAMICVECTOR_H__
/*--------------------------------- HEADER FILES -------------------------------------------------*/
#include <stddef.h> /* size_t */

/*----------------------------------- TYPEDEF ----------------------------------------------------*/

typedef struct dynamic_vector vector_t;

/*------------------------------------------------------------------------------------------------*/

/* (in .c file:)
 
struct dynamic_vector
{
	void *vector;
	size_t num_of_elements;
	size_t capacity;
	size_t element_size;
};

*/
/*-----------------------------------------------------------------------------------------------*/

/* DESCRIPTION:
 * Function that creates a new dynamic vector. Memory will be specially allocated according
 * to parameters: (initial) 'capacity' - max number of elements, and 'element_size' - size of each vector element.
 * In case of allocation failure, NULL will be returned.
 * In order to avoid memory leaking, the VectorDestroy function is requiered in end of use.
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * size_t capacity: max number of elements initial vector can hold
 * size_t element_size: size of each dynamic vector element 
 *
 * RETURN VALUE:
 * vector_t * : pointer to new dynamic vector created, NULL if allocation failed.
 */
vector_t *VectorCreate(size_t capacity, size_t element_size);

/*-----------------------------------------------------------------------------------------------*/

/* DESCRIPTION:
 * Function that destroyes dynamic vector specirfied by pointer. 
 * Previously allocated memory will be freed.
 * Any remaining data will be lost 
 * In case of pointer pointing to NULL, behavior is undefined
 *
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * vector_t	* dynamic_vector : pointer to dynamic vector
 * 
 * RETURN VALUE: 
 * no return value
 */
void VectorDestroy(vector_t *dynamic_vector);

/*-----------------------------------------------------------------------------------------------*/

/* DESCRIPTION:
 * Function that returns a pointer to an element in the dynamic vector, specified by index. 
 * In case of pointer pointing to NULL, behavior is undefined
 * 
 * Warning: using pointer returned by VectorGetElement function to manipulate values outside range of elements currently
 * 			held in dynamic vector results in undefined behavior.
 *  
 *
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * vector_t *dynamic_vector:	pointer to dymanic vector,
 * size_t index of specified element 
 *
 * RETURN VALUE:
 * void * :pointer to the specified element
 */
void *VectorGetElement(const vector_t *dynamic_vector, size_t index);

/*-----------------------------------------------------------------------------------------------*/

/* DESCRIPTION:
 * Function that removes the last element in a dynamic vector.
 * In case of pointer pointing to NULL, behavior is undefined.
 *
 * Time complexity: O(n) 
 *
 * PARAMETERS:
 * vector_t *dynamic_vector: pointer to dynamic vector
 *
 * RETURN VALUE: 
 * int : zero if reallocation was not needed or succeeded, non-zero if failed
 */
int VectorPopBack(vector_t *dynamic_vector);

/*-----------------------------------------------------------------------------------------------*/

/* DESCRIPTION:
 * Function that adds an element at the end of a dynamic vector. 
 * In case of pointer pointing to NULL, the behavior is undefined.
 *
 * Time complexity: O(n) 
 *
 * PARAMETERS:
 * vector_t *dynamic_vector:	pointer to dynamic vector
 * void * data : pointer to data to be added
 *
 * RETURN VALUE:
 * int : zero if reallocation was not needed or succeeded, non-zero if failed
 */
int VectorPushBack(vector_t *dynamic_vector, const void *element);

/*-----------------------------------------------------------------------------------------------*/

/* DESCRIPTION:
 * Function that returns current number of elements held by dynamic vector. 
 * In case of pointer pointing to NULL, behavior is undefined.
 *
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * const vector_t *dynamic_vector :	pointer to dynamic vector
 *
 * RETURN VALUE:
 * size_t : current number of elements in dynamic vector
 */
size_t VectorSize(const vector_t *dynamic_vector);

/*-----------------------------------------------------------------------------------------------*/

/* DESCRIPTION:
 * Function that returns current total capacity (max number of elements) of dynamic vector. 
 * In case of pointer pointing to NULL, behavior is undefined.
 *
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * const vector_t *dynamic_vector :	pointer to dynamic vector
 *
 * RETURN VALUE:
 * size_t : current total capacity (max number of elements) of dynamic vector
 */
size_t VectorCapacity(const vector_t *dynamic_vector);

/*-----------------------------------------------------------------------------------------------*/

/* DESCRIPTION:
 * Auxilary function that reallocates memory for dynamic vector.
 * In case of pointer pointing to NULL, behavior is undefined.
 *
 * Time complexity: O(n)
 *
 * PARAMETERS:
 * vector_t *dynamic_vector : pointer to dynamic vector
 * size_t new_size : new specified capacity reallocated vector
 *
 * RETURN VALUE:
 * int : zero if reallocation succeeded, non-zero if failed
 */
int VectorResize(vector_t *dynamic_vector, size_t new_size);  

#endif /* __ILRD_OL95_DYNAMICVECTOR_H__ */
