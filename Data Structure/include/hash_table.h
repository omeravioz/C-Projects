/*******************************************************************************
*                             DS - HASH_TABLE - HEADER FILE        
* 												 		 
* Description: API of Hash Table functions.
* Date: 18.11.2020										 
* InfinityLabs OL95										 
*******************************************************************************/
/*--------------------------------- Header Guard -----------------------------*/

#ifndef __ILRD_OL95_HASH_TABLE_H__
#define __ILRD_OL95_HASH_TABLE_H__

/*-------------------------- HEADER FILES ------------------------------------*/
#include <stddef.h> /* size_t */

/*------------------------- TYPEDEF ------------------------------------------*/
typedef struct hash_table hash_table_t;

/* hash function:
genrate index for givin data*/
typedef size_t (*hash_function_t)(const void *data);

/* match function:
returns 1 if match, else 0*/
typedef int (*is_match_hash_t)(const void *hash_data, const void *input_data);

/* hash function:
preform an action on data*/
typedef int (*hash_action_t)(void *data, void *param);


/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that creates a new hash table.
 * Memory will be specially allocated.
 * In case of memory allocation failure, NULL will be returned.
 * In order to avoid memory leaks, the hash_tableDestroy function is requiered at
 * end of use.
 *
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * size_t table_size - the hash table array size.
 * is_match_t match_func - the function to match data in slist.
 * hash_function_t hash_func - genrate indexes from data.
 *
 * RETURN VALUE:
 * hash_table_t *hash_table - pointer to new created hash table, NULL if memory
 * allocation failed.
 */
 
hash_table_t *HashTableCreate(size_t table_size, hash_function_t hash_func, is_match_hash_t match_func);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that destroys a specified hash table . 
 * Previously allocated memory will be freed.
 * All remaining data will be lost 
 *
 * Time complexity: O(n) 
 *
 * PARAMETERS:
 * hash_table_t *hash_table - pointer to a hash table to be destroyed
 *
 * (In case of pointer pointing to invalid hash table, behavior is undefined)
 *
 * RETURN VALUE: 
 * no return value
 */
void HashTableDestroy(hash_table_t *hash_table);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that creates a new hash table entry that holds specified data 
 * and adds it to the hash table. 
 * Memory will be allocated for new hash table entry.
 *
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * hash_table_t *hash_table -	pointer to hash table to be added to. 
 * void * data - pointer to data to be added.
 *
 *(In case of pointers pointing to invalid hash table or data, behavior is undefined)
 *
 * RETURN VALUE:
 * if failed return non zero, else return 0.
 */
int HashTableInsert(hash_table_t *hash_table,  void *data);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that removes data entry from the hash table.
 * Frees memory that was previously allocated for the entry that is being 
 * removed.
 * 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * hash_table_t *hash_table- pointer to hash table.
 * const void *data - data to remove.
 * (In case of pointer pointing to invald hash table, behavior is undefined)
 *
 * RETURN VALUE:
 * no return value
 */
void HashTableRemove(hash_table_t *hash_table, const void *data);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that returns the specified data in a hash table. 
 * 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * hash_table_t *hash_table - pointer to hash table to be searched in.
 * void *data - pointer to the data that is being searched for. 
 * 
 * (In case of pointers pointing to invalid data, hash table, or function
 * behavior is undefined)
 *
 * RETURN VALUE:
 * if found returns the data, else returns NULL;
 * 
 */
void *HashTableFind(const hash_table_t *hash_table, const void *data);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that returns current number of entries in a hash_table. 
 *
 * Time complexity: O(n)
 *
 * PARAMETERS:
 * hash_table_t *hash_table - pointer to a hash_table. 
 *
 * (In case of pointer pointing to invalid hash_table, behavior is undefined)
 *
 * RETURN VALUE:
 * size_t - current number of entries in a hash_table.
 */ 
size_t HashTableSize(const hash_table_t *hash_table);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that checks if a hash_table is empty or not.
 * 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * const hash_table_t *hash_table - pointer to a hash_table.
 *
 * (In case of pointer pointing to invalid hash_table, behavior is undefined)
 *
 * RETURN VALUE:
 * int - one if hash_table is empty, zero if hash_table is not empty.
 */

int HashTableIsEmpty(const hash_table_t *hash_table);

/* DESCRIPTION:
 * A function that that preform action on all each entry.
 * 
 * Time complexity: O(n)
 *
 * PARAMETERS:
 * const hash_table_t *hash_table - pointer to a hash_table.
 * hash_action_t hash_action - the action to be preformed
 * void *param - param to the action function
 *
 * (In case of pointer pointing to invalid hash_table, behavior is undefined)
 *
 * RETURN VALUE:
 * if failed return non zero, else return 0.
 */


int HashTableForEach(const hash_table_t *hash_table, hash_action_t hash_action, void *param);


/*Advanced*/
/* for noami and yoni :) */
/*size/hashtablesize*/

double HashTableLoad(const hash_table_t *hash_table);

double HashTableSD(const hash_table_t *hash_table);



/*----------------------------------------------------------------------------*/
#endif /* __ILRD_OL95_HASH_TABLE_H__ */
