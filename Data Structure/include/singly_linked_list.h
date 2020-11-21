/*******************************************************************************
*                             DS - SINGLY_LINKED_LIST - HEADER FILE        
* 												 		 
* Description: API of singly linked list functions.
* Worksheet: 3											 
* Date: 04.10.2020										 
* InfinityLabs OL95										 
*******************************************************************************/
/*--------------------------------- Header Guard -----------------------------*/

#ifndef __ILRD_OL95_SINGLY_LINKED_LIST_H__
#define __ILRD_OL95_SINGLY_LINKED_LIST_H__

/*-------------------------- HEADER FILES ------------------------------------*/
#include <stddef.h> /* size_t */

/*------------------------- TYPEDEF ------------------------------------------*/
 
typedef struct singly_linked_list slist_t;
 
typedef struct node node_t;

typedef node_t *slist_iter_t;

/* pointer to a comparison function: returns 0 if match is found, returns non-
zero if not found */
typedef int (*compare_t)(const void *data1, const void *data2);

/* pointer to a user defined action function to be performed on each iterator.
Recieves as parameters data to be executed on and an additional parmeter. 
Returns zero if execution succeeded, non-zero if failed */
typedef int (*action_function_t)(void *data, void *param);

/* (in .c file:)

struct node 
{
	void *data;
	node_t *next;
};

struct singly_linked_list
{
	node_t *begin;
	node_t *end;
};

*/
/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that creates a new singly linked list.
 * Memory will be specially allocated.
 * In case of memory allocation failure, NULL will be returned.
 * In order to avoid memory leaks, the SListDestroy function is requiered at
 * end of use.
 *
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * function does not take any parameters
 *
 * RETURN VALUE:
 * slist_t * - pointer to new created singly linked list, NULL if memory
 * allocation failed.
 */
 
slist_t *SListCreate(void);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that destroys a specified singly linked list . 
 * Previously allocated memory will be freed.
 * All remaining data will be lost 
 *
 * Time complexity: O(n)
 *
 * PARAMETERS:
 * slist_t *list - pointer to a singly linked list to be destroyed
 *
 * (In case of pointer pointing to invalid list, behavior is undefined)
 *
 * RETURN VALUE: 
 * no return value
 */
 
void SListDestroy(slist_t *list);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that creates a new list iterator that holds specified data 
 * and adds it to the end of a singly linked list. 
 * Memory will be allocated for new list iterator.
 *
 * Time complexity: O(1) 
 *
 * PARAMETERS:
 * slist_t *list -	pointer to singly linked list to be added to. 
 * void * data - pointer to data to be added.
 *
 *(In case of pointers pointing to invalid list or data, behavior is undefined)
 *
 * RETURN VALUE:
 * int - zero if memory allocation succeeded, non-zero if failed.
 */
int SListPushBack(slist_t *list, const void *data);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that removes a iterator from the end of a singly linked list.
 * Frees memory that was previously allocated for the iterator that is being 
 * removed.
 * 
 * Time complexity: O(1) 
 *
 * PARAMETERS:
 * slist_t *list - pointer to singly linked list.
 *
 * (In case of pointer pointing to invald list, behavior is undefined)
 *
 * RETURN VALUE:
 * no return value
 */
 
void SListPopBack(slist_t *list);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that creates a new list iterator that ponits to specified data and
 * inserts it into a singly linked list before next_iterator.
 * Memory will be allocated for the new iterator. 
 *
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * const slist_t *list - pointer to a singly linked list.
 * slist_iter_t next_iterator -  a list iterator, before which data will
 * be inserted.
 * void * data - pointer to the data to be inserted.
 * 
 * (In case of pointers pointing to invalid data, list, or 
 * iterator, behavior is undefined) 
 *
 * RETURN VALUE:
 * int - zero if memory allocation succeded, non-zero if failed.
 */
 int SListInsertBefore
 				  (slist_t *list, slist_iter_t next_iterator, const void *data);


/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that removes a specified iterator from a singly linked list.
 * Frees memory that was previously allocated for the iterator that is being
 * removed.
 * 
 * Time complexity: O(1) 
 *
 * PARAMETERS:
 * slist_t *list -	pointer to a singly linked list.
 * slist_iter_t iterator - a iterator that is to be removed.
 *
* (In case of pointer pointing to invalid list, or in case of invalid
 * iterator, behavior is undefined) 
 *
 * RETURN VALUE:
 * no return value
 */
 
void SListRemove(slist_t *list, slist_iter_t iterator);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that returns an iterator in a singly linked list that
 * holds specified data.
 * 
 * Time complexity: O(n)
 *
 * PARAMETERS:
 * slist_t *list - pointer to singly linked list to be searched in.
 * compare_t compare - pointer to a user defined function that compares
 * specified data to data in the list. 
 * void *data - pointer to the data that is being searched for. 
 * 
 * (In case of pointers pointing to invalid data, list, or function
 * behavior is undefined)
 *
 * RETURN VALUE:
 * slist_iter_t -  the list iterator that holds specified data.
 * In case data is not found, return end iterator.
 */
 
slist_iter_t SListFindIter
			   (const slist_t *list, const compare_t compare, const void *data);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that iterates over a specified sub-list of iterators in a singly
 * linked list an executes a specified function on each one of them.
 * 
 * Time complexity: O(n)
 *
 * PARAMETERS:
 * slist_iter_t begin - poninter to the first iterator of a sub-list.
 * slist_iter_t end - poninter to the last iterator of a sub-list.
 * const action_function func - pointer to a function to be executed on all 
 * iterators in the sub-list 
 * void *param - pointer to additional parameter 
 * 
 * (In case of pointers pointing to invalid data, or in case of invalid
 * iterators, behavior is undefined) 
 *
 * RETURN VALUE:
 * int * - zero if all executions succeeded, non-zero if one or more failed.
 */
 
 int SListForEachIter
 		(slist_iter_t first, slist_iter_t last, const action_function_t func,
 		void *param);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that returns current number of iterators in a singly linked list. 
 *
 * Time complexity: O(n)
 *
 * PARAMETERS:
 * slist_t *list - pointer to a singly linked list. 
 *
 * (In case of pointer pointing to invalid list, behavior is undefined)
 *
 * RETURN VALUE:
 * size_t - current number of iterator in a singly linked list.
 */
 
size_t SListSize(const slist_t *list);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that returns the begin iterator of a singly linked list.
 * 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * const slist_t *list - pointer to a singly linked list.
 *
 * (In case of pointer pointing invalid list, behavior is undefined)
 *
 * RETURN VALUE:
 * slist_iter_t - the begin iterator of a singly linked list.
 */
 
slist_iter_t SListBegin(const slist_t *list);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that returns the end iterator of a singly linked list.
 * 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * const slist_t *list - pointer to a singly linked list.
 *
 * (In case of pointer pointing to invalid list, behavior is undefined)
 *
 * RETURN VALUE:
 * slist_iter_t -  the end iterator of a singly linked list.
 */
 
slist_iter_t SListEnd(const slist_t *list);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that returns a the next iterator in a singly linked list.
 * 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * const slist_t *list - pointer to a singly linked list.
 * slist_iter_t iterator - iterator of a singly linked list.
 *
 * (In case of pointer pointing to invalid list, or in case of invalid
 * iterator, behavior is undefined)
 *
 * RETURN VALUE:
 * slist_iter_t - the next iterator in a singly linked list.
 */

slist_iter_t SListNextIter(slist_iter_t iterator); 

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that returns a pointer pointing to the data in
 * a specified iterator of a singly linked list .
 * 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * const slist_t *list - pointer to a singly linked list.
 * slist_iter_t iterator - iterator of a singly linked list.
 *
 * (In case of pointer pointing to invalid list, or in case of invalid
 * iterator, behavior is undefined)
 *
 * RETURN VALUE:
 * void * - poinetr to the data pointed to by specified iterator.
 */

void *SListGetData(slist_iter_t iterator);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that checks if a singly linked list is empty or not.
 * 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * const slist_t *list - pointer to a singly linked list.
 *
 * (In case of pointer pointing to invalid list, behavior is undefined)
 *
 * RETURN VALUE:
 * int - '1' if list is empty, '0' if list is not empty.
 */

int SListIsEmpty(const slist_t *list);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that checks if two iterators in a singly linked list are the same 
 * or not.
 * 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * slist_iter_t iterator1 - first iterator to be compared.
 * slist_iter_t iterator1 - second iterator to be compared.
 * 
 * (In case of invalid iterators, behavior is undefined)
 *
 * RETURN VALUE:
 * int - '1' if iterators are same, '0' if not.
 */

int SListIsSameIter(slist_iter_t iterator1, slist_iter_t iterator2);

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
void SListAppend(slist_t *src, slist_t *dest);

/*----------------------------------------------------------------------------*/

#endif /* __ILRD_OL95_SINGLY_LINKED_LIST_H__ */
