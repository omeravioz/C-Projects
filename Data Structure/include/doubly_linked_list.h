/*******************************************************************************
*********************************HEADER-FILE************************************
* Description:  API of Circular doubly_linked_list functions.
* Date: 11.10.2020										 
* InfinityLabs OL95	
********************************************************************************
*******************************************************************************/
/*--------------------------------- Header Guard -----------------------------*/

#ifndef __ILRD_OL95_DOUBLY_LINKED_LIST_H__
#define __ILRD_OL95_DOUBLY_LINKED_LIST_H__

/*-------------------------- HEADER FILES ------------------------------------*/
#include <stddef.h> /* size_t */

/*------------------------- TYPEDEF ------------------------------------------*/

 
typedef struct node node_t;

typedef struct doubly_linked_list dlist_t;

typedef struct doubly_linked_list_iter dlist_iter_t;

struct doubly_linked_list_iter
{
	node_t *internal;
};
/* (in .c file:)

struct node 
{
	void *data;
	node_t *next;
	node_t *prev;
};
struct doubly_linked_list 
{
	node_t head;
	node_t tail;
	
};

*/

/* pointer to a comparison function: returns 1 if match is found, returns 
zero if not found */
typedef int (*is_match_t)(const void *data1, const void *data2);

/* pointer to a user defined action function to be performed on each iterator.
Recieves as parameters data to be executed on and an additional parmeter. 
Returns zero if execution succeeded, non-zero if failed */
typedef int (*action_t)(void *data, void *param);



/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that creates a new doubly linked list.
 * Memory will be specially allocated.
 * In case of memory allocation failure, NULL will be returned.
 * In order to avoid memory leaks, the DListDestroy function is required at
 * end of use.
 *
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * function does not take any parameters
 *
 * RETURN VALUE:
 * dlist_t * - pointer to new created doubly linked list, NULL if memory
 * allocation failed.
 */
 
dlist_t *DListCreate(void);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that destroys a specified doubly linked list . 
 * Previously allocated memory will be freed.
 * All remaining data will be lost 
 * In case of pointers pointing to invalid dlist, behavior is undefined.
 * Time complexity: O(n)
 *
 * PARAMETERS:
 * dlist_t *list - pointer to a doubly linked list to be destroyed
 *
 *
 * RETURN VALUE: 
 * no return value
 */
 
void DListDestroy(dlist_t *list);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that creates a new node that holds specified data 
 * and adds it to the end of a doubly linked list. 
 * Memory will be allocated for new list iterator.
 *
 * Time complexity: O(1) 
 *
 * PARAMETERS:
 * dlist_t *list -	pointer to doubly linked list to be added to. 
 * void * data - pointer to data to be added.
 *
 * In case of pointers pointing to invalid dlist or data, behavior is undefined.
 *
 * RETURN VALUE:
 * dlist_iter_t - if succeed returns new node iter, if failed return end iter.
 */
 dlist_iter_t DListPushBack(dlist_t *list, const void *data);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that removes a node from the end of a doubly linked list.
 * Frees memory that was previously allocated for the node that is being 
 * removed.
 * 
 * Time complexity: O(1) 
 *
 * PARAMETERS:
 * dlist_t *list - pointer to doubly linked list.
 *
 * In case of pointers pointing to invalid dlist or data, behavior is undefined.
 *
 * RETURN VALUE:
 * no return value
 */
 
void DListPopBack(dlist_t *list);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that creates a new list node that points to specified data and
 * inserts it into a doubly linked list before next_iterator.
 * Memory will be allocated for the new node. 
 *
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * const dlist_t *list - pointer to a doubly linked list.
 * dlist_iter_t next_iterator -  a list iterator, before which data will
 * be inserted.
 * void * data - pointer to the data to be inserted.
 * 
 * In case of pointers pointing to invalid dlist, iterator
 * or data behavior is undefined.
 *
 * RETURN VALUE:
 * dlist_iter_t - if succeed returns new node iter, if failed return end iter.
 */
 dlist_iter_t DListInsert
                 (dlist_t *list, dlist_iter_t next_iterator, const void *data);
/*----------------------------------------------------------------------------*/
/* DESCRIPTION:
 * A function that removes a specified node from a doubly linked list.
 * Frees memory that was previously allocated for the  node that is being
 * removed.
 * 
 * Time complexity: O(1) 
 *
 * PARAMETERS:
 * dlist_t *list -	pointer to a doubly linked list.
 * dlist_iter_t iterator -  a iterator to the node to be removed.
 *
 * In case of pointers pointing to invalid dlist, iterator
 * behavior is undefined.
 *
 * RETURN VALUE:
 * dlist_iter_t - returns next iterator.
 */
 
dlist_iter_t DListRemove(dlist_t *list, dlist_iter_t iterator);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that returns an iterator in a doubly linked list that
 * holds specified data.
 * 
 * Time complexity: O(n)
 *
 * PARAMETERS:
 *  dlist_iter_t from -  pointer to the first iterator of a sub-list.
 * dlist_iter_t to -  pointer to the last iterator of a sub-list.
 * is_match_t is_match - pointer to a user defined function that compares
 * specified data to data in the list. 
 * void *data - pointer to the data that is being searched for. 
 * 
 * In case of pointers pointing to invalid dlist, iterator
 * or data behavior is undefined.
 *
 * RETURN VALUE:
 * dlist_iter_t -  the list left iterator that holds specified data.
 * In case data is not found, return to iterator.
 */
 
dlist_iter_t DListFind
    (dlist_iter_t from, dlist_iter_t to, is_match_t is_match, const void *data);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that iterates over a specified sub-list of nodes in a doubly
 * linked list an executes a specified function on each one of them.
 * 
 * Time complexity: O(n)
 *
 * PARAMETERS:
 * dlist_iter_t from - pointer to the first iterator of a sub-list.
 * dlist_iter_t to - pointer to the last iterator of a sub-list.
 * const action_function func - pointer to a function to be executed on all 
 * iterators in the sub-list 
 * void *param - pointer to additional parameter 
 * 
 *
 * RETURN VALUE:
 * int * - zero if all executions succeeded, non-zero if one or more failed.
 */
 
 int DListForEach
 	(dlist_iter_t from, dlist_iter_t to, action_t func, void *param);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that returns current number of nodes in a doubly linked list. 
 *
 * Time complexity: O(n)
 *
 * PARAMETERS:
 * dlist_t *list - pointer to a doubly linked list. 
 *
 * In case of pointers pointing to invalid dlist behavior is undefined.
 * 
 *
 * RETURN VALUE:
 * size_t - current number of nodes in a doubly linked list.
 */
 
size_t DListSize(const dlist_t *list);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that returns the begin iterator of a doubly linked list.
 * 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * const dlist_t *list - pointer to a doubly linked list.
 *
 * In case of pointers pointing to invalid dlist behavior is undefined.
 *
 * RETURN VALUE:
 * dlist_iter_t - the begin iterator of a doubly linked list.
 */
 
dlist_iter_t DListBegin(const dlist_t *list);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that returns the  tail iterator of a doubly linked list.
 * 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * const dlist_t *list - pointer to a doubly linked list.
 *
 * In case of pointers pointing to invalid dlist behavior is undefined.
 *
 * RETURN VALUE:
 * dlist_iter_t -  the  tail iterator of a doubly linked list.
 */
 
dlist_iter_t DListEnd(const dlist_t *list);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that returns a the next iterator in a doubly linked list.
 * 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * const dlist_t *list - pointer to a doubly linked list.
 * dlist_iter_t iterator - iterator of a doubly linked list.
 *
 * In case of pointers pointing to invalid dlist behavior is undefined.
 *
 * RETURN VALUE:
 * dlist_iter_t - the next iterator in a doubly linked list.
 */

dlist_iter_t DListNextIter(dlist_iter_t iterator); 
/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that returns a the Previous iterator in a doubly linked list.
 * 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * const dlist_t *list - pointer to a doubly linked list.
 * dlist_iter_t iterator - iterator of a doubly linked list.
 *
 * In case of pointers pointing to invalid dlist behavior is undefined.
 *
 * RETURN VALUE:
 * dlist_iter_t - the previous iterator in a doubly linked list.
 */

dlist_iter_t DListPrevIter(dlist_iter_t iterator); 
/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that returns a pointer pointing to the data in
 * a specified iterator of a doubly linked list .
 * 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * const dlist_t *list - pointer to a doubly linked list.
 * dlist_iter_t iterator - iterator of a doubly linked list.
 *
 * In case of pointers pointing to invalid dlist behavior is undefined.
 *
 * RETURN VALUE:
 * void * - poinetr to the data pointed to by specified iterator.
 */

void *DListGetData(dlist_iter_t iterator);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that checks if a doubly linked list is empty or not.
 * 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * const dlist_t *list - pointer to a doubly linked list.
 *
 * In case of pointers pointing to invalid dlist behavior is undefined.
 *
 * RETURN VALUE:
 * int - 1 if list is empty, zero if list is not empty.
 */

int DListIsEmpty(const dlist_t *list);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that checks if two iterators in a doubly linked list are the same 
 * or not.
 * 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * dlist_iter_t iterator1 - first iterator to be compared.
 * dlist_iter_t iterator1 - second iterator to be compared.
 * 
 * In case of pointers pointing to invalid dlist behavior is undefined.
 *
 * RETURN VALUE:
 * int - return 1 if iterator are same, zero if not.
 */

int DListIsSameIter(dlist_iter_t iterator1, dlist_iter_t iterator2);

/*----------------------------------------------------------------------------*/
/* DESCRIPTION:
 * A function that splice doubly linked list.
 * The function inserts a list from - to after dest_iter and return th iterator
 * after the to iterator
 * 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * dlist_t dest_iter - pointer to the dest
 * dlist_iter_t from - pointer to the first iterator of a sub-list.
 * dlist_iter_t to - pointer to the last iterator of a sub-list.
 * In case of pointers pointing to invalid dlist, iterator
 * or data behavior is undefined
 *
 * RETURN VALUE:
 * dlist_iter_t  the next node of the last node that was added
 */
dlist_iter_t DListSplice
              (dlist_iter_t dest_iter, dlist_iter_t from, dlist_iter_t to);
/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that returns a doubly linked list that
 * holds all wanted matches.
 * 
 * Time complexity: O(n)
 *
 * PARAMETERS:
 *  dlist_iter_t from - pointer to the first iterator of a sub-list.
 * dlist_iter_t to -  pointer to the last iterator of a sub-list.
 * is_match_t is_match - pointer to a user defined function that compares
 * specified data to data in the list. 
 * void *data - pointer to the data that is being searched for. 
 * dlist_t output_list - pointer to matched data list.	
 *  
 * 
 * In case of pointers pointing to invalid dlist, iterator
 * or data behavior is undefined.
 *
 * RETURN VALUE:
 * int  - zero if all executions succeeded, non-zero if one or more failed.
 */
int DListMultiFind
          (dlist_iter_t from, dlist_iter_t to, is_match_t is_match, 
                                       const void *data, dlist_t *output_list);

#endif /* __ILRD_OL95_DOUBLY_LINKED_LIST_H__ */
