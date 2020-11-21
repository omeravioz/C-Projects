/*******************************************************************************
*                             DS - QUEUE - HEADER FILE        
* 												 		 
* Description: API of Queue based on slist functions.
* Worksheet: DS Queue										 
* Date: 06.10.2020										 
* InfinityLabs OL95										 
*******************************************************************************/
/*--------------------------------- Header Guard -----------------------------*/

#ifndef __ILRD_OL95_QUEUE_H__
#define __ILRD_OL95_QUEUE_H__

/*-------------------------- HEADER FILES ------------------------------------*/
#include <stddef.h> /* size_t */

/*------------------------- TYPEDEF ------------------------------------------*/
 
typedef struct queue queue_t;



/* DESCRIPTION:
 * A function that creates a new queue.
 * Memory will be specially allocated.
 * In case of memory allocation failure, NULL will be returned.
 * In order to avoid memory leaks, the QueueDestroy function is requiered at
 * end of use.
 *
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * function does not take any parameters
 *
 * RETURN VALUE:
 * queue_t * - pointer to new created queue, NULL if memory
 * allocation failed.
 */ 
 
queue_t *QueueCreate(void);

/* DESCRIPTION:
 * A function that destroys a specified queue . 
 * Previously allocated memory will be freed.
 * All remaining data will be lost 
 *
 * Time complexity: O(n)
 *
 * PARAMETERS:
 * queue_t *queue - pointer to a queue to be 
 * destroyed
 *
 * (In case of pointer pointing to invalid queue, behavior is undefined)
 *
 * RETURN VALUE: 
 * no return value
 */
 
void QueueDestroy(queue_t *queue);

/* DESCRIPTION:
 * A function that creates a new queue element that holds
 * specified data 
 * and adds it to the rear of a queue. 
 * Memory will be allocated for new queue element.
 *
 * Time complexity: O(1) 
 *
 * PARAMETERS:
 * queue_t *queue -	pointer to queue to be added to. 
 * void *data - pointer to data to be added.
 *
 *(In case of pointers pointing to invalid queue or data, behavior is undefined)
 *
 * RETURN VALUE:
 * int - zero if memory allocation succeeded, non-zero if failed.
 */
int QueueEnqueue(queue_t *queue, const void *data);

/* DESCRIPTION:
 * A function that removes a element from the front of a queue.
 * Frees memory that was previously allocated for the element that is being 
 * removed.
 * 
 * Time complexity: O(1) 
 *
 * PARAMETERS:
 * queue_t *queue - pointer to queue.
 *
 * (In case of pointer pointing to invald queue, behavior is undefined)
 *
 * RETURN VALUE:
 * no return value
 */
void QueueDequeue(queue_t *queue);

/* DESCRIPTION:
 * A function that returns current number of elements in a queue. 
 *
 * Time complexity: O(n)
 *
 * PARAMETERS:
 * queue_t *queue - pointer to a queue. 
 *
 * (In case of pointer pointing to invalid queue, behavior is undefined)
 *
 * RETURN VALUE:
 * size_t - current number of elements in a queue.
 */
size_t QueueSize(const queue_t *queue);

/* DESCRIPTION:
 * A function that returns the front element of a queue.
 * 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * const queue_t *queue - pointer to a queue.
 *
 * (In case of pointer pointing invalid queue, behavior is undefined)
 *
 * RETURN VALUE:
 * void * - pointer to data in the front of a queue.
 */
void *QueuePeek(const queue_t *queue);

/* DESCRIPTION:
 * A function that checks if a queue is empty or not.
 * 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * const queue_t *queue - pointer to a queue.
 *
 * (In case of pointer pointing to invalid variable, behavior is undefined)
 *
 * RETURN VALUE:
 * int - one if queue is empty, zero if queue is not empty.
 */
int QueueIsEmpty(const queue_t *queue);

/* DESCRIPTION:
 * A function that appends source queue to destination queue.
 * 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * queue_t *queue1 - pointer to queue1.
 * queue_t *queue2 - pointer to queue2.
 * (In case of pointer pointing to invalid variable, behavior is undefined)
 *
 * RETURN VALUE:
 * no return value.
 */
void QueueAppend(queue_t *src, queue_t *dest);

#endif /*__ILRD_OL95_QUEUE_H__*/
