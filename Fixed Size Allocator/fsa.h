/******************************************************************************
*                                 fsa/OL95 	     	                 	  	  *                
*              	 Written by: ________ Approved by:_____________ 	  	  *                  
*	 		            		    27.9.20   						  		  *		  
******************************************************************************/

/*----------------------------- Header Guard --------------------------------*/

#ifndef __ILRD_OL95_FSA_H__
#define __ILRD_OL95_FSA_H__

/*-------------------------------- Libraries --------------------------------*/

#include <stddef.h>    /* size_t */

/*----------------------------- Typedefs ------------------------------------*/

typedef struct fsa fsa_t;

/*--------------------------- Functions declarations ------------------------*/

/* DESCRIPTION:
 * Function for initializing a fixed size allocation system.
 * Memory pools of block_size will be available for allocation.
 * In case the pointer is pointing to an invalid address or NULL,
 * behavior will be undefined
 * Time complexity: O(n)
 *
 * @param:
 * void *segment:	pointer to beginning of memory segment to by managed
 * size_t block_size:	requested size of memory blocks
 * size_t total_bytes:	total number of bytes for segment
 *
 * @return:
 * Returns *fsa_t is success, else return NULL.
 */
fsa_t *FSAInit(void *segment, size_t total_bytes, size_t block_size);


/* DESCRIPTION:
 * Function for allocated a fixed size block from segment.
 * In case the pointer is pointing to an invalid address or NULL,
 * behavior will be undefined
 * Time complexity: O(1)
 *
 * @param:
 * fsa_t *fsa:			pointer to memory segment
 *
 * @return:
 * Returns pointer to fixed size allocated memory
 */
void *FSAAlloc(fsa_t *fsa);


/* DESCRIPTION:
 * Function for freeing allocated memory from fixed size memory segment.
 * In case any of the pointers is pointing to an invalid address or to NULL,
 * the behavior will be undefined.
 * Time complexity: O(1)
 *
 * @param:
 * fsa_t *fsa:				pointer to memory segment
 * void *allocated_mem:		pointer to allocated block to be freed
 */
void FSAFree(fsa_t *fsa, void *allocated_mem);


/* DESCRIPTION:
 * Function for counting the remaining blocks free for allocation
 * in the given fixed size allocation segment.
 * In case the pointer is pointing to an invalid address or NULL,
 * the behavior will be undefined.
 * Time complexity: O(n)
 *
 * @param:
 * const fsa_t *fsa:		pointer to memory segment
 *
 * @return:
 * Returns the number of free blocks
 */
size_t FSACountFree(const fsa_t *fsa);


/* DESCRIPTION:
 * Function for calculating suggested bytes amount for malloc according to
 * user's requested block_size and num_of_blocks.
 * Time complexity: O(1)
 *
 * @param:
 * size_t num_of_blocks:	requested number of blocks
 * size_t block_size:		requested block size
 *
 * @return:
 * Returns the suggested bytes amount for allocating
 */
size_t FSASuggestSize(size_t num_of_blocks, size_t block_size);


#endif /* __ILRD_OL95_FSA_H__ */
