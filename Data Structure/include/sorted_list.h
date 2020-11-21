/*******************************************************************************
*********************************HEADER-FILE************************************
* Description: API of sorted_list functions.
* Date: 12.10.2020										 
* InfinityLabs OL95	
********************************************************************************
*******************************************************************************/
/*--------------------------------- HEADER GUARD -----------------------------*/

#ifndef __ILRD_OL95_SORTED_LIST_H__
#define __ILRD_OL95_SORTED_LIST_H__

/*-------------------------- HEADER FILES ------------------------------------*/
#include <stddef.h> /* size_t */
#include "doubly_linked_list.h"

/*------------------------- TYPEDEF ------------------------------------------*/

 
typedef struct sorted_list sorted_list_t;

typedef struct sorted_list_iter sorted_list_iter_t;


struct sorted_list_iter
{
    dlist_iter_t sorted_iter;
#ifndef NDEBUG
    sorted_list_t *list_owner; 
#endif    
};

/* (in .c file:)

#include "doubly_linked_list.h"

struct sorted_list 
{
	dlist_t *sorted_list;
	compare_t compare;
};

*/
/* The list sorted will be in ascending order
 
   pointer to a comparison function: 
 * returns an integer less than, equal to, or greater than zero
 */
typedef int (*compare_t)(const void *input_data, const void *iter_data);


/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that creates a new sorted list.
 * Memory will be specially allocated.
 * In case of memory allocation failure, NULL will be returned.
 * In order to avoid memory leaks, the SortedListDestroy function is required at
 * end of use.
 *
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * compare_t compare - function to compare data.
 *
 * RETURN VALUE:
 * sorted_list_t * - pointer to new created sorted list, NULL if memory
 * allocation failed.
 */
 
sorted_list_t *SortedListCreate(compare_t compare);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that destroys a specified sorted list . 
 * Previously allocated memory will be freed.
 * All remaining data will be lost.
 * In case of pointers pointing to invalid list, behavior is undefined.
 * Time complexity: O(n)
 *
 * PARAMETERS:
 * sorted_list_t *list - pointer to a sorted list to be destroyed
 *
 *
 * RETURN VALUE: 
 * no return value
 */
 
void SortedListDestroy(sorted_list_t *list);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that removes a node from the end of a sorted list.
 * Frees memory that was previously allocated for the node that is being 
 * removed.
 * 
 * Time complexity: O(1) 
 *
 * PARAMETERS:
 * sorted_list_t *list - pointer to sorted list.
 *
 * In case of pointers pointing to invalid list or data, behavior is undefined.
 *
 * RETURN VALUE:
 * no return value
 */
 
void SortedListPopBack(sorted_list_t *list);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that creates a new node that points to specified data and
 * inserts it into a sorted list.
 * Memory will be allocated for the new node. 
 *
 * Time complexity: O(n)
 *
 * PARAMETERS:
 * const sorted_list_t *list - pointer to a sorted list.
 * void * data - pointer to the data to be inserted.
 * 
 * In case of pointers pointing to invalid list, iterator
 * or data behavior is undefined.
 *
 * RETURN VALUE:
 * sorted_list_iter_t - if succeed returns new node iter, if failed return end iter.
 */
 sorted_list_iter_t SortedListInsert
                 (sorted_list_t *list, const void *data);
                 
/*----------------------------------------------------------------------------*/
/* DESCRIPTION:
 * A function that removes a specified node from a sorted list.
 * Frees memory that was previously allocated for the node that is being
 * removed.
 * 
 * Time complexity: O(1) 
 *
 * PARAMETERS:
 * sorted_list_t *list - pointer to a sorted list.
 * sorted_list_iter_t iterator - a iterator to the node to be removed.
 *
 * In case of pointers pointing to invalid list, iterator
 * behavior is undefined.
 *
 * RETURN VALUE:
 * sorted_list_iter_t - returns next iterator.
 */
 
sorted_list_iter_t SortedListRemove
                           (sorted_list_t *list, sorted_list_iter_t iterator);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that returns an iterator in a sorted list that
 * holds specified data.
 * 
 * Time complexity: O(n)
 *
 * PARAMETERS:
 * const sorted_list_t *list - pointer to a sorted list.
 * void *data - pointer to the data that is being searched for. 
 * 
 * In case of pointers pointing to invalid list, iterator, data or from - to are 
 * not owned by the same lists behavior is undefined.
 *
 * RETURN VALUE:
 * sorted_list_iter_t - the list left iterator that holds specified data.
 * In case data is not found, returns "end".
 */
 
sorted_list_iter_t SortedListFind(sorted_list_t *list, const void *data);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that returns an iterator in a sorted list that
 * holds specified data.
 * 
 * Time complexity: O(n)
 *
 * PARAMETERS:
 * const sorted_list_t *list - pointer to a sorted list.
 * void *data - pointer to the data that is being searched for.
 * is_match_t is_match - pointer to a match function. 
 * 
 * In case of pointers pointing to invalid list, iterator, data or from - to are 
 * not owned by the same lists behavior is undefined.
 *
 * RETURN VALUE:
 * sorted_list_iter_t - the list left iterator that holds specified data.
 * In case data is not found, returns "end".
 */
 
sorted_list_iter_t SortedListFindIf
                  (sorted_list_t *list, is_match_t is_match, const void *data);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that iterates over a specified sub-list of nodes in a sorted
 * list an executes a specified function on each one of them.
 * If the action_t func will unsort the list, the function will not sort the 
 * result again.
 * 
 * Time complexity: O(n)
 *
 * PARAMETERS:
 * sorted_list_iter_t from - pointer to the first iterator of a sub-list.
 * sorted_list_iter_t to - pointer to the last iterator of a sub-list.
 * const action_function func - pointer to a function to be executed on all 
 * iterators in the sub-list 
 * void *param - pointer to additional parameter 
 * 
 *
 * RETURN VALUE:
 * int * - zero if all executions succeeded, non-zero if one or more failed.
 */
 
 int SortedListForEach
	(sorted_list_iter_t from, sorted_list_iter_t to, action_t func, void *param);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that returns current number of nodes in a sorted list. 
 *
 * Time complexity: O(n)
 *
 * PARAMETERS:
 * sorted_list_t *list - pointer to a sorted list. 
 *
 * In case of pointers pointing to invalid list behavior is undefined.
 * 
 *
 * RETURN VALUE:
 * size_t - current number of nodes in a sorted list.
 */
 
size_t SortedListSize(const sorted_list_t *list);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that returns the begin iterator of a sorted list.
 * 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * const sorted_list_t *list - pointer to a sorted list.
 *
 * In case of pointers pointing to invalid list behavior is undefined.
 *
 * RETURN VALUE:
 * sorted_list_iter_t - the begin iterator of a sorted list.
 */
 
sorted_list_iter_t SortedListBegin(const sorted_list_t *list);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that returns the  tail iterator of a sorted list.
 * 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * const sorted_list_t *list - pointer to a sorted list.
 *
 * In case of pointers pointing to invalid list behavior is undefined.
 *
 * RETURN VALUE:
 * sorted_list_iter_t -  the  tail iterator of a sorted list.
 */
 
sorted_list_iter_t SortedListEnd(const sorted_list_t *list);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that returns a the next iterator in a sorted list.
 * 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * const sorted_list_t *list - pointer to a sorted list.
 * sorted_list_iter_t iterator - iterator of a sorted list.
 *
 * In case of pointers pointing to invalid list behavior is undefined.
 *
 * RETURN VALUE:
 * sorted_list_iter_t - the next iterator in a sorted list.
 */

sorted_list_iter_t SortedListNextIter(sorted_list_iter_t iterator); 
/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that returns a the Previous iterator in a sorted list.
 * 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * const sorted_list_t *list - pointer to a sorted list.
 * sorted_list_iter_t iterator - iterator of a sorted list.
 *
 * In case of pointers pointing to invalid list behavior is undefined.
 *
 * RETURN VALUE:
 * sorted_list_iter_t - the previous iterator in a sorted list.
 */

sorted_list_iter_t SortedListPrevIter(sorted_list_iter_t iterator); 
/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that returns a pointer pointing to the data in
 * a specified iterator of a sorted list .
 * 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * const sorted_list_t *list - pointer to a sorted list.
 * sorted_list_iter_t iterator - iterator of a sorted list.
 *
 * In case of pointers pointing to invalid list behavior is undefined.
 *
 * RETURN VALUE:
 * void * - poinetr to the data pointed to by specified iterator.
 */

void *SortedListGetData(sorted_list_iter_t iterator);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that checks if a sorted list is empty or not.
 * 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * const sorted_list_t *list - pointer to a sorted list.
 *
 * In case of pointers pointing to invalid list behavior is undefined.
 *
 * RETURN VALUE:
 * int - return 1 if list is empty, zero if list is not empty.
 */

int SortedListIsEmpty(const sorted_list_t *list);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that checks if two iterators in a sorted list are the same 
 * or not.
 * 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * sorted_list_iter_t iterator1 - first iterator to be compared.
 * sorted_list_iter_t iterator1 - second iterator to be compared.
 * 
 * In case of pointers pointing to invalid list behavior is undefined.
 *
 * RETURN VALUE:
 * int - return 1 if iterator are same, zero if not.
 */

int SortedListIsSameIter
 			(sorted_list_iter_t iterator1, sorted_list_iter_t iterator2);

/*----------------------------------------------------------------------------*/
/* DESCRIPTION:
 * A function that marge two sorted lists into one.
 * The function inserts a list from - to (of the same list) to dest sorted.
 * 
 * Time complexity: O(n)
 *
 * PARAMETERS:
 * sorted_list_t dest_list - pointer to the destination list
 * sorted_list_t src_list - pointer to the destination list
 * 
 * In case of pointers pointing to invalid lists behavior is undefined
 *
 * RETURN VALUE:
 * none
 */
void SortedListMerge
  (sorted_list_t *dest_list, sorted_list_t *src_list);
/*----------------------------------------------------------------------------*/

#endif /* __ILRD_OL95_SORTED_LIST_H____ */
