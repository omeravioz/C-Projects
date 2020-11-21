/*******************************************************************************
*                             DS - BINARY_SORTED_TREE - HEADER FILE        
* 												 		 
* Description: API of binary sorted tree functions.
* Worksheet: 3											 
* Date: 05.11.2020										 
* InfinityLabs OL95										 
*******************************************************************************/
/*--------------------------------- Header Guard -----------------------------*/

#ifndef __ILRD_OL95_BINARY_SORTED_TREE_H__
#define __ILRD_OL95_BINARY_SORTED_TREE_H__

/*-------------------------- HEADER FILES ------------------------------------*/
#include <stddef.h> /* size_t */

/*------------------------- TYPEDEF ------------------------------------------*/
 
typedef struct binary_sorted_tree bst_t;

typedef struct bst_node bst_node_t;
 
typedef bst_node_t *bst_iter_t;

/* pointer to a comparison function: 
<0 tree_data < input_data
=0 tree_data = input_data
>0 itree_data > input_data*/
typedef int (*compare_function_t)(const void *tree_data, const void *input_data, void *params);

/* pointer to a user defined action function to be performed on each iterator.
Recieves as parameters data to be executed on and an additional parmeter. 
Returns zero if execution succeeded, non-zero if failed */
typedef int (*action_function_t)(void *data, void *param);


/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that creates a new bst.
 * Memory will be specially allocated.
 * In case of memory allocation failure, NULL will be returned.
 * In order to avoid memory leaks, the BstDestroy function is requiered at
 * end of use.
 *
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * compare_t compare - the function to compare between nodes
 *
 * RETURN VALUE:
 * bst_t * - pointer to new created bst, NULL if memory
 * allocation failed.
 */
 
bst_t *BSTCreate(compare_function_t compare ,void *params);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that destroys a specified bst . 
 * Previously allocated memory will be freed.
 * All remaining data will be lost 
 *
 * Time complexity: O(n)
 *
 * PARAMETERS:
 * bst_t *bst - pointer to a bst to be destroyed
 *
 * (In case of pointer pointing to invalid bst, behavior is undefined)
 *
 * RETURN VALUE: 
 * no return value
 */
void BSTDestroy(bst_t *bst);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that creates a new bst iterator that holds specified data 
 * and adds it to the correct place in the bst. 
 * Memory will be allocated for new bst iterator.
 *
 * Time complexity: O(n) avg = log(n); worst_case = n;
 *
 * PARAMETERS:
 * bst_t *bst -	pointer to bst to be added to. 
 * void * data - pointer to data to be added.
 *
 *(In case of pointers pointing to invalid bst or data, behavior is undefined)
 *
 * RETURN VALUE:
 * Returns the iterator that was inserted. If failed - returns root
 */
bst_iter_t BSTInsert(bst_t *bst, void *data);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that removes a iterator from the bst.
 * Frees memory that was previously allocated for the iterator that is being 
 * removed.
 * 
 * Time complexity: O(n) 
 *
 * PARAMETERS:
 * bst_t *bst - pointer to bst.
 * bst_iter_t *iter - iterator to remove
 * (In case of pointer pointing to invald bst, behavior is undefined)
 *
 * RETURN VALUE:
 * no return value
 */
void BSTRemove(bst_iter_t iter);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that returns an iterator in a bst that
 * holds specified data.
 * 
 * Time complexity: O(n)
 *
 * PARAMETERS:
 * bst_t *bst - pointer to bst to be searched in.
 * compare_t compare - pointer to a user defined function that compares
 * specified data to data in the bst. 
 * void *data - pointer to the data that is being searched for. 
 * 
 * (In case of pointers pointing to invalid data, bst, or function
 * behavior is undefined)
 *
 * RETURN VALUE:
 * bst_iter_t -  the bst iterator that holds specified data.
 * if not found returns root;
 * 
 */
bst_iter_t BSTFind(bst_t *bst, void *data);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that iterates over a specified sub-bst of iterators in a bst
 * and executes a specified function on each one of them.
 * 
 * Time complexity: O(n)
 *
 * PARAMETERS:
 * bst_t *bst - poninter to the first iterator of a bst.
 * const action_function func - pointer to a function to be executed on all 
 * iterators in the bst and not destroy the ordering of the tree
 * void *param - pointer to additional parameter 
 * 
 * (In case of pointers pointing to invalid data, or in case of invalid
 * iterators, behavior is undefined) 
 * from - include
 * to not included
 * RETURN VALUE:
 * int - zero if all executions succeeded, func return value on first exe failed.
 */
int BSTForEach(bst_iter_t from, bst_iter_t to, action_function_t func, void *param);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that returns current number of iterators in a bst. 
 *
 * Time complexity: O(n)
 *
 * PARAMETERS:
 * bst_t *bst - pointer to a bst. 
 *
 * (In case of pointer pointing to invalid bst, behavior is undefined)
 *
 * RETURN VALUE:
 * size_t - current number of iterator in a bst.
 */ 
size_t BSTSize(const bst_t *bst);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that returns the begin(min-data) iterator of a bst.
 * 
 * Time complexity: O(n)
 *
 * PARAMETERS:
 * const bst_t *bst - pointer to a bst.
 *
 * (In case of pointer pointing invalid bst, behavior is undefined)
 *
 * RETURN VALUE:
 * bst_iter_t - the begin iterator of a bst.
 */
bst_iter_t BSTBegin(const bst_t *bst);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that returns the end(dummy - root) iterator of a bst.
 * 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * const bst_t *bst - pointer to a bst.
 *
 * (In case of pointer pointing to invalid bst, behavior is undefined)
 *
 * RETURN VALUE:
 * bst_iter_t -  the end iterator of a bst. return dummy - root
 */
bst_iter_t BSTEnd(const bst_t *bst);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that returns a the next iterator in a bst.
 * 
 * Time complexity: O(n)
 *
 * PARAMETERS:
 * const bst_t *bst - pointer to a bst.
 * bst_iter_t iterator - iterator of a bst.
 *
 * (In case of pointer pointing to invalid bst, or in case of invalid
 * iterator, behavior is undefined)
 *
 * RETURN VALUE:
 * bst_iter_t - the next iterator in a bst. if not exist return dummy - root
 */
bst_iter_t BSTNext(bst_iter_t iterator); 

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that returns a the prev iterator in a bst.
 * 
 * Time complexity: O(n)
 *
 * PARAMETERS:
 * const bst_t *bst - pointer to a bst.
 * bst_iter_t iterator - iterator of a bst.
 *
 * (In case of pointer pointing to invalid bst, or in case of invalid
 * iterator, behavior is undefined)
 *
 * RETURN VALUE:
 * bst_iter_t - the prev iterator in a bst. if not exist return root
 */
bst_iter_t BSTPrev(bst_iter_t iterator);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that returns a pointer pointing to the data in
 * a specified iterator of a bst .
 * 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * const bst_t *bst - pointer to a bst.
 * bst_iter_t iterator - iterator of a bst.
 *
 * (In case of pointer pointing to invalid bst, or in case of invalid
 * iterator, behavior is undefined)
 *
 * RETURN VALUE:
 * void * - poinetr to the data pointed to by specified iterator.
 */

void *BSTGetData(bst_iter_t iterator);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that checks if a bst is empty or not.
 * 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * const bst_t *bst - pointer to a bst.
 *
 * (In case of pointer pointing to invalid bst, behavior is undefined)
 *
 * RETURN VALUE:
 * int - one if bst is empty, zero if bst is not empty.
 */

int BSTIsEmpty(const bst_t *bst);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that checks if two iterators in a bst are the same or not.
 * 
 * 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * bst_iter_t iterator1 - first iterator to be compared.
 * bst_iter_t iterator2 - second iterator to be compared.
 * 
 * (In case of invalid iterators, behavior is undefined)
 *
 * RETURN VALUE:
 * int - one if iterator are same, zero if not.
 */

int BSTIsSameIter(bst_iter_t iterator1, bst_iter_t iterator2);


/*----------------------------------------------------------------------------*/

#endif /* __ILRD_OL95_BINARY_SORTED_TREE_H__ */
