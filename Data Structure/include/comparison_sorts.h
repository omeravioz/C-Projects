/*******************************************************************************
*********************************HEADER-FILE************************************
* Description:  API of Comparison Sorts.
* Date: 4.11.2020										 
* InfinityLabs OL95	
********************************************************************************
*******************************************************************************/
/*--------------------------------- Header Guard -----------------------------*/

#ifndef __ILRD_OL95_COMPSORT_H__
#define __ILRD_OL95_COMPSORT_H__

/*-------------------------- HEADER FILES ------------------------------------*/

#include <stddef.h> /* size_t */

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that sorts an array of integers.
 * Time complexity: O(n^2)
 *
 * PARAMETERS:
 * arr - array to sort
 * size - size of an array to sort
 *
 * RETURN VALUE:
 * no return value
 * 
 */
 
void BubbleSort(int *arr, size_t size);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that sorts an array of integers.
 * Time complexity: O(n^2)
 *
 * PARAMETERS:
 * arr - array to sort
 * size - size of an array to sort
 *
 * RETURN VALUE:
 * no return value
 * 
 */
 
void SelectionSort(int *arr, size_t size);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that sorts an array of integers.
 * Time complexity: O(n^2)
 *
 * PARAMETERS:
 * arr - array to sort
 * size - size of an array to sort
 *
 * RETURN VALUE:
 * no return value
 * 
 */
 
void InsertionSort(int *arr, size_t size);

/*----------------------------------------------------------------------------*/

#endif /* __ILRD_OL95_COMPSORT_H__ */
