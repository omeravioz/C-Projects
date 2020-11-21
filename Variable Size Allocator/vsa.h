/******************************************************************************
*                                 vsa/OL95 	     	                 	  	  *                

*	 		            		   21.10.20   						  		  *		  
******************************************************************************/

/*----------------------------- Header Guard --------------------------------*/

#ifndef __ILRD_OL95_VSA_H__
#define __ILRD_OL95_VSA_H__

/*-------------------------------- Libraries --------------------------------*/

#include <stddef.h>    /* size_t */

/*----------------------------- Typedefs ------------------------------------*/

/*
in c file:

#ifndef NDEBUG
#define DEBUG_ONLY(code) code
#else
#define DEBUG_ONLY(code)
#endif

typedef struct block_header block_h_t;

struct vsa
{
	size_t total_size; 
};

struct block_header
{
	long block_size; 
DEBUG_ONLY(
	vsa_t *owner;
)
};

*/

typedef struct vsa vsa_t;

/*--------------------------- Functions declarations ------------------------*/

/* DESCRIPTION:
 * Function for initializing a variable size allocation system.
 * Memory pool will be available for allocation.
 * In case the pointer is pointing to an invalid address or NULL,
 * behavior will be undefined
 * Time complexity: O(1)
 *
 * @param:
 * void *segment:		pointer to beginning of memory segment to by managed
 * size_t segment_size:	total size of segment to be managed
 *
 * @return:
 * Returns pointer to beginning of memory allocation pool
 */
vsa_t *VSAInit(void *segment, size_t segment_size);


/* DESCRIPTION:
 * Function for allocated a variable size block from segment.
 * In case their is no free space to allocate, NULL will be returned.
 * In case the pointer is pointing to an invalid address or NULL,
 * behavior will be undefined
 * Time complexity: O(n)
 *
 * @param:
 * vsa_t *vsa:				pointer to memory segment
 * size_t requested_size:	size of requested memory block for allocation
 *
 * @return:
 * Returns pointer to fixed size allocated memory
 */
void *VSAAlloc(vsa_t *vsa, size_t requested_size);


/* DESCRIPTION:
 * Function for freeing allocated memory from variable size memory segment.
 * In case any the vsa pointer is pointing to an invalid address or to NULL,
 * the behavior will be undefined.
 * Time complexity: O(1)
 *
 * @param:
 * vsa_t *vsa:				pointer to memory segment
 * void *allocated_mem:		pointer to allocated block to be freed
 */
void VSAFree(vsa_t *vsa, void *allocated_mem);


/* DESCRIPTION:
 * Function for finding the size of the current biggest memory chunk
 * available in the variable size allocation segment.
 * In case the pointer is pointing to an invalid address or NULL,
 * the behavior will be undefined.
 * Time complexity: O(n)
 *
 * @param:
 * const vsa_t *vsa:		pointer to memory segment
 *
 * @return:
 * Returns the size of the current biggest memory chunk available
 */
size_t VSALargestBlockAvailable(const vsa_t *vsa);


#endif /* __ILRD_OL95_VSA_H__ */
