/*******************************************************************************
*********************************HEADER-FILE************************************
* Description: API of Circular Buffer functions.
* Date: 08.10.2020										 
* InfinityLabs OL95	
********************************************************************************
*******************************************************************************/



/*******************************************************************************
*                            Header Guard                                      *
*******************************************************************************/
#ifndef __ILRD_OL95_CIRCULARBUFFER_H__
#define __ILRD_OL95_CIRCULARBUFFER_H__

/*******************************************************************************
*                            HEADER FILES                                      *
*******************************************************************************/
#include <stddef.h> /* size_t */

/*******************************************************************************
*                                  TYPEDEF                                     *
*******************************************************************************/ 

typedef struct circular_buffer c_buff_t;

/******************************************************************************/


/* DESCRIPTION:
 * Function that creates a new Circular Buffer. Memory will be specially allocated according
 * to parameters: capacity - max number of elements
 * In case of allocation failure, NULL will be returned.
 * In order to avoid memory leaking, the CBuffDestroy function is required in end of use.
 * Time complexity: O(n)
 *
 * PARAMETERS:
 * size_t capacity: max number of elements initial Circular Buffer can hold
 *
 * RETURN VALUE:
 * c_buff_t * : pointer to new Circular Buffer created, NULL if allocation failed.
 */
c_buff_t *CBuffCreate(size_t capacity);

/******************************************************************************/
/* DESCRIPTION:
 * Function that destroys Circular Buffer specified by pointer. 
 * Previously allocated memory will be freed.
 * Any remaining data will be lost 
 * In case of pointers pointing to invalid cbuff, behavior is undefined.
 *
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * c_buff_t * CBuff: pointer to CBuff
 * 
 * RETURN VALUE: 
 * no return value
 */
void CBuffDestroy(c_buff_t *cbuff);

/******************************************************************************/
/* DESCRIPTION:
 * Function that returns a number of bytes that was read from CBuff. 
 * In case of pointers pointing to invalid cbuff or data, behavior is undefined.
 * If count is bigger then the CBuff data the function will read the current data in the CBuff.
 *
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * c_buff_t *CBuff: pointer to CBuff.
 * dest: pointer to read destination. 
 * count: number of bytes to read from CBuff.
 *
 * RETURN VALUE:
 * size_t : number of bytes that was read from CBuff.
 */
size_t CBuffRead(c_buff_t *cbuff, void *dest, size_t count);

/******************************************************************************/
/* DESCRIPTION:
 * Function that adds data to the end of a CBuff. 
 * In case of pointers pointing to invalid CBuff or src, behavior is undefined.
 * Time complexity: O(1) 
 *
 * PARAMETERS:
 * c_buff_t *CBuff: pointer to CBuff.
 * src: pointer to write source. 
 * count: number of bytes to Write to CBuff.
 *
 * RETURN VALUE:
 * size_t : number of bytes that was written to CBuff.
 */
size_t CBuffWrite(c_buff_t *cbuff, void *src, size_t count);

/******************************************************************************/
/* DESCRIPTION:
 * Function that checks if the CBuff is empty. 
 * In case of pointers pointing to invalid cbuff, behavior is undefined.
 *
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * const c_buff_t *CBuff: pointer to CBuff
 *
 * RETURN VALUE:
 * int : one if the CBuff is empty, zero otherwise.
 */
int CBuffIsEmpty(const c_buff_t *cbuff);

/******************************************************************************/
/* DESCRIPTION:
 * Function that returns current number of free space. 
 * In case of pointers pointing to invalid cbuff, behavior is undefined.
 *
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * const c_buff_t *CBuff: pointer to CBuff
 *
 * RETURN VALUE:
 * size_t : current total free space.
 */
size_t CBuffFreeSpace(const c_buff_t *cbuff);

/******************************************************************************/
/* DESCRIPTION:
 * Function that checks the capacity of CBuff. 
 * In case of pointers pointing to invalid cbuff, behavior is undefined.
 *
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * const c_buff_t *CBuff: pointer to CBuff
 *
 * RETURN VALUE:
 * size_t : capacity of CBuff.
 */
size_t CBuffCapacity(const c_buff_t *cbuff);

/******************************************************************************/
#endif /* __ILRD_OL95CBuff_H__ */
