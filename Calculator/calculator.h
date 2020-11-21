/*******************************************************************************
*                  DS - CALCULATOR - HEADER FILE        
* 												 		 
* Description: API of CALCULATOR functions.
* Worksheet: 									 
* Date: 10.11.2020										 
* InfinityLabs OL95										 
*******************************************************************************/
/*---------------------------- Header Guard ----------------------------------*/

#ifndef __ILRD_OL95_CALCULATOR_H__
#define __ILRD_OL95_CALCULATOR_H__


typedef enum calc_status
{
	SUCCESS = 0,
	DIVIDE_BY_0 = 1,
	NUM_AFTER_NUM = 2,
	OP_AFTER_OP = 3,
	PARENTHESIS_UNBALANCED = 4,
	INVALID_CHAR = 5,
	MALLOC_FAILED = 6,
	SYNTAX_ERROR = 7,
	OTHER
}calc_status_t;


/******************************************************************************/
/* DESCRIPTION:
 * A function that calculate the exp string.
 * 
 * Time complexity: O(n)
 *
 * PARAMETERS:
 * const char *exp - the expression to calculate;
 * double * res - pointer to the result. If the operation fails -   res will be 0.
 * 
 * in case of invalid pointer to exp or res - undefined behavior
 * RETURN VALUE:
 * calc_status_t - success or relevant error;
 */  
calc_status_t Calc(const char *exp, double *res);

#endif /*_ILRD_OL95_CALCULATOR_H_*/
