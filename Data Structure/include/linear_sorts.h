/*******************************************************************************
*********************************HEADER-FILE************************************
* Description:  API of Linear Sorts.
* Date: 4.11.2020										 
* InfinityLabs OL95	
********************************************************************************
*******************************************************************************/
/*--------------------------------- Header Guard -----------------------------*/

#ifndef __ILRD_OL95_LINEAR_SORTS_H__
#define __ILRD_OL95_LINEAR_SORTS_H__

/*-------------------------- HEADER FILES ------------------------------------*/
#include <stddef.h> /* size_t */

/* DESCRIPTION:
 * A function that sorts an array of integers.
 * Time complexity: O(n + k)
 *
 * PARAMETERS:
 * array - array to sort
 * array_size - size of an array to sort
 *
 * RETURN VALUE:
 * void - no return value
 * 
 */
void CountingSort(int *arr, size_t size);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that sorts an array of integers.
 * Time complexity: O(n + k)
 *
 * PARAMETERS:
 * array - array to sort
 * array_size - size of an array to sort
 *
 * RETURN VALUE:
 * void - no return value
 * 
 */
void RadixSort(int *arr, size_t size);

/*----------------------------------------------------------------------------*/

#endif /* __ILRD_OL95_LINEAR_SORTS_H__ */
