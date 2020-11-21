/*******************************************************************************
*                  DS - PRIORITY QUEUE - HEADER FILE        
* 												 		 
* Description: API of Priority Queue functions.
* Worksheet: DS Priority Queue										 
* Date: 14.10.2020										 
* InfinityLabs OL95										 
*******************************************************************************/
/*---------------------------- Header Guard ----------------------------------*/

#ifndef __ILRD_OL95_PRIORITY_QUEUE_H__
#define __ILRD_OL95_PRIORITY_QUEUE_H__

/*-------------------------- HEADER FILES ------------------------------------*/
#include <stddef.h> /* size_t */
#include "sorted_list.h" /* sl functions declaration */
/*------------------------- TYPEDEF ------------------------------------------*/
 
typedef struct pq pq_t;

/* in c file

	**The highest priorty will be in the tail**

#include "sorted_list.h"
struct pq
{
	sorted_list_t *sorted_list;
};

*/

/* DESCRIPTION:
 * A function that creates a new priority pq.
 * Memory will be specially allocated.
 * In case of memory allocation failure, NULL will be returned.
 * In order to avoid memory leaks, the PQueueDestroy function is required at
 * end of use.
 *
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * cmp - the users compare function
 * const void *new_data - new data to be compared
 * const void *existing_data - existing data to be compared
 * RETURN VALUE:
 * pq_t * - pointer to new created pq, NULL if memory
 * allocation failed.
 */ 
 
pq_t *PQCreate(int (*cmp)( const void *new_data, const void *existing_data));
 
/* DESCRIPTION:
 * A function that destroys a specified priority pq . 
 * Previously allocated memory will be freed.
 * All remaining data will be lost 
 *
 * Time complexity: O(n)
 *
 * PARAMETERS:
 * pq_t *pq - pointer to a pq to be 
 * destroyed
 *
 * (In case of pointer pointing to invalid pq, behavior is undefined)
 *
 * RETURN VALUE: 
 * no return value
 */
 
void PQDestroy(pq_t *pq);

/* DESCRIPTION:
 * A function that creates a new pq element that holds
 * specified data 
 * and adds it to the pq considering its priority. 
 * Memory will be allocated for new pq element.
 *
 * Time complexity: O(n) 
 *
 * PARAMETERS:
 * pq_t *pq -	pointer to pq to be added to. 
 * void *data - pointer to data to be added.
 *
 *(In case of pointers pointing to invalid pq or data, behavior is undefined)
 *
 * RETURN VALUE:
 * int - zero if memory allocation succeeded, non-zero if failed.
 */
int PQEnqueue(pq_t *pq, const void *data);

/* DESCRIPTION:
 * A function that removes a element from the pq with the highest priority.
 * Frees memory that was previously allocated for the element that is being 
 * removed.
 * 
 * Time complexity: O(1) 
 *
 * PARAMETERS:
 * pq_t *pq - pointer to pq.
 *
 * (In case of pointer pointing to invald pq, behavior is undefined)
 *
 * RETURN VALUE:
 * void * - a pointer to the data
 */
void *PQDequeue(pq_t *pq);

/* DESCRIPTION:
 * A function that returns current number of elements in a pq. 
 *
 * Time complexity: O(n)
 *
 * PARAMETERS:
 * pq_t *pq - pointer to a pq. 
 *
 * (In case of pointer pointing to invalid pq, behavior is undefined)
 *
 * RETURN VALUE:
 * size_t - current number of elements in a pq.
 */
size_t PQSize(const pq_t *pq);

/* DESCRIPTION:
 * A function that returns the next element to be Dequeue.
 * 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * const pq_t *pq - pointer to a pq.
 *
 * (In case of pointer pointing invalid pq, behavior is undefined)
 *
 * RETURN VALUE:
 * void * - pointer to data in the front of a pq.
 */
void *PQPeek(const pq_t *pq);

/* DESCRIPTION:
 * A function that checks if a pq is empty or not.
 * 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * const pq_t *pq - pointer to a pq.
 *
 * (In case of pointer pointing to invalid variable, behavior is undefined)
 *
 * RETURN VALUE:
 * int - one if pq is empty, zero if pq is not empty.
 */
int PQIsEmpty(const pq_t *pq);

/* DESCRIPTION:
 * A function that erase a specific element.
 * 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * const pq_t *pq - pointer to a pq.
 * is_match - the user compare function between param that we want to find 
 * and the data in the list
 * void *params - the parameter for the is_match 
 * (In case of pointer pointing to invalid variable, behavior is undefined)
 *
 * RETURN VALUE:
 * void * - pointer to data of element.
 */
void *PQErase(pq_t *pq, 
          int(*is_match)(const void *data, const void *params), void *params);

/* DESCRIPTION:
 * A function that clear the queue to be empty.
 * 
 * Time complexity: O(n)
 *
 * PARAMETERS:
 *  pq_t *pq - pointer to a pq.
 * 
 * (In case of pointer pointing to invalid variable, behavior is undefined)
 *
 * RETURN VALUE:
 * no return value.
 */
void PQClear(pq_t *pq);



#endif /*_ILRD_OL95_BIT_ARRAY_H_*/
