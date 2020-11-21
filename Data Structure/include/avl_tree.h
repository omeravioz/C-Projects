/*******************************************************************************
*                             DS - AVL_TREE - HEADER FILE        
* 												 		 
* Description: API of binary sorted tree (recursive) functions.
* Date: 15.11.2020										 
* InfinityLabs OL95										 
*******************************************************************************/
/*--------------------------------- Header Guard -----------------------------*/

#ifndef __ILRD_OL95_AVL_TREE_H__
#define __ILRD_OL95_AVL_TREE_H__

/*-------------------------- HEADER FILES ------------------------------------*/
#include <stddef.h> /* size_t */
#include "singly_linked_list.h" /* slist_t */

/*------------------------- TYPEDEF ------------------------------------------*/


typedef enum traversal_order
{
	PREORDER = 0,
	INORDER,
	POSTORDER
} traversal_order_t;

typedef struct avl_tree avl_tree_t;

typedef struct avl_tree_node avl_tree_node_t;

/* pointer to a comparison function: 
<0 tree_data < input_data
=0 tree_data = input_data
>0 tree_data > input_data */
typedef int (*compare_function_t)(const void *tree_data, const void *input_data);

/* match function:
returns 1 if match, else 0*/
typedef int (*is_match_t)(const void *tree_data, const void *param);

/* pointer to a user defined action function to be performed on each iterator.
Recieves as parameters data to be executed on and an additional parmeter. 
Returns zero if execution succeeded, non-zero if failed */
typedef int (*action_func_avl_t)(void *data, void *param);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that creates a new avl.
 * Memory will be specially allocated.
 * In case of memory allocation failure, NULL will be returned.
 * In order to avoid memory leaks, the avl_treeDestroy function is requiered at
 * end of use.
 *
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * compare_t compare - the function to compare between nodes
 *
 * RETURN VALUE:
 * avl_tree_t *avl_tree - pointer to new created avl, NULL if memory
 * allocation failed.
 */
 
avl_tree_t *AVLTreeCreate(compare_function_t compare);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that destroys a specified avl . 
 * Previously allocated memory will be freed.
 * All remaining data will be lost 
 *
 * Time complexity: O(n) - postorder
 *
 * PARAMETERS:
 * avl_tree_t *avl_tree - pointer to a avl to be destroyed
 *
 * (In case of pointer pointing to invalid avl, behavior is undefined)
 *
 * RETURN VALUE: 
 * no return value
 */
void AVLTreeDestroy(avl_tree_t *avl_tree);




/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that creates a new avl iterator that holds specified data 
 * and adds it to the correct place in the avl. 
 * Memory will be allocated for new avl iterator.
 *
 * Time complexity: O(log(n))
 *
 * PARAMETERS:
 * avl_tree_t *avl_tree -	pointer to avl to be added to. 
 * void * data - pointer to data to be added.
 *
 *(In case of pointers pointing to invalid avl or data, behavior is undefined)
 *
 * RETURN VALUE:
 * if failed return -1, else return 0.
 */
int AVLTreeInsert(avl_tree_t *avl_tree, void *data);



/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that removes a iterator from the avl.
 * Frees memory that was previously allocated for the iterator that is being 
 * removed.
 * 
 * Time complexity: O(log(n))
 *
 * PARAMETERS:
 * avl_tree_t *avl_tree- pointer to avl.
 * void *data - node to remove.
 * (In case of pointer pointing to invald avl, behavior is undefined)
 *
 * RETURN VALUE:
 * no return value
 */
void AVLTreeRemove(avl_tree_t *avl_tree, void *data);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that returns an iterator in a avl that
 * holds specified data.
 * 
 * Time complexity: O(log(n))
 *
 * PARAMETERS:
 * avl_tree_t *avl_tree - pointer to avl to be searched in.
 * compare_t compare - pointer to a user defined function that compares
 * specified data to data in the avl. 
 * void *data - pointer to the data that is being searched for. 
 * 
 * (In case of pointers pointing to invalid data, avl, or function
 * behavior is undefined)
 *
 * RETURN VALUE:
 * if found returns the value of the key, else returns NULL;
 * 
 */
void *AVLTreeFind(const avl_tree_t *avl_tree, void *data);

/* DESCRIPTION:

 * 
 * Time complexity: O(1)
 *
 * 
 */
size_t AVLTreeHeight(const avl_tree_t *avl_tree);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that iterates over a specified sub-avl_tree of iterators in a avl_tree
 * and executes a specified function on each one of them.
 * 
 * Time complexity: O(n)
 *
 * PARAMETERS:
 * avl_tree_t *avl_tree - poninter to the first iterator of a avl_tree.
 * const action_function func - pointer to a function to be executed on all 
 * iterators in the avl_tree and not destroy the ordering of the tree
 * void *param - pointer to additional parameter 
 * 
 * (In case of pointers pointing to invalid data, or in case of invalid
 * iterators, behavior is undefined) 
 * from - include
 * to not included
 * RETURN VALUE:
 * int - zero if all executions succeeded, func return value on first exe failed.
 */
int AVLTreeForEach(avl_tree_t *avl_tree, action_func_avl_t func, void *param, traversal_order_t order);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that returns current number of iterators in a avl_tree. 
 *
 * Time complexity: O(n)
 *
 * PARAMETERS:
 * avl_tree_t *avl_tree - pointer to a avl_tree. 
 *
 * (In case of pointer pointing to invalid avl_tree, behavior is undefined)
 *
 * RETURN VALUE:
 * size_t - current number of iterator in a avl_tree.
 */ 
size_t AVLTreeCount(const avl_tree_t *avl_tree);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that checks if a avl_tree is empty or not.
 * 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * const avl_tree_t *avl_tree - pointer to a avl_tree.
 *
 * (In case of pointer pointing to invalid avl_tree, behavior is undefined)
 *
 * RETURN VALUE:
 * int - one if avl_tree is empty, zero if avl_tree is not empty.
 */

int AVLTreeIsEmpty(const avl_tree_t *avl_tree);


/* DESCRIPTION:

 * A function that searches a avl_tree and lists all matches in 
 * a given sinly linked list 
 *
 * Time complexity: O(n)
 *
 * PARAMETERS:
 * const avl_tree_t *avl_tree - pointer to a avl_tree.
 * is_match_t is_match - pointer to match function.
 * const void *param - params for match function.
 * slist_t *list - pointer to the list of matches.
 *
 * (In case of pointer pointing to invalid avl_tree, behavior is undefined)
 *
 * RETURN VALUE:
 * int - 0 if list allocation succeeded else 1
 */

int AVLMultiFind(const avl_tree_t *avl_tree, 
				 is_match_t is_match,
				 const void *param,
				 slist_t *list);

/* DESCRIPTION:

 * A function that searches a avl_tree, lists all matches in 
 * a given sinly linked list and removes the matches from the tree. 
 * 
 * Time complexity: O(n + (k *log(n)))
 *
 * PARAMETERS:
 * const avl_tree_t *avl_tree - pointer to a avl_tree.
 * is_match_t is_match - pointer to match function.
 * const void *param - params for match function.
 * slist_t *list - pointer to the list of matches.
 *
 * (In case of pointer pointing to invalid avl_tree, behavior is undefined)
 *
 * RETURN VALUE:
 * int - 0 if list allocation succeeded else 1
 */
 			 
int AVLMultiRemove(const avl_tree_t *avl_tree, 
				 is_match_t is_match,
				 const void *param,
				 slist_t *list);

/*----------------------------------------------------------------------------*/

#endif /* __ILRD_OL95_AVL_TREE_H__ */
