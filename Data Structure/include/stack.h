/**********************************************************************************************
*                              	         stack/OL95 	     	                              *
*                 	 Written by: Cohen Yonatan. Approved by: __________ 	                  *  
*	 			      					   27.9.20   									      *
**********************************************************************************************/

/*--------------------------------- Header Guard ----------------------------------------*/

#ifndef __ILRD_OL95_STACK_H__
#define __ILRD_OL95_STACK_H__

/*------------------------------------ Libraries ----------------------------------------*/

#include <stddef.h>    /* size_t   */

/*------------------------------------ Typedefs -----------------------------------------*/

typedef struct stack stack_t;

/*--------------------------- Functions declarations ------------------------------------*/

/* DESCRIPTION:
 * Function for creating a new available stack. Memory will be specially allocated.
 * In case of failure allocating memory, NULL will be returned.
 * In order to avoid memory leaking, the StackDestroy function is requiered in end of use.
 * Time complexity: O(1)
 *
 * @param:
 * size_t capacity:		requested capacity of stack
 * size_t element_size: requested size of elements
 *
 * @return:
 * Returns pointer to new stack created, or NULL if failed allocating memory
 *
 */
stack_t *StackCreate(size_t capacity, size_t element_size);


/* DESCRIPTION:
 * Function for destroying given stack. memory will be freed
 * and any remaining data will be lost 
 * In case of pointer pointing to NULL, the behavior will be undefined
 * Time complexity: O(1)
 *
 * @param:
 * stack_t stack:	pointer to stack
 *
 */
void StackDestroy(stack_t *stack);


/* DESCRIPTION:
 * Function for pushing a new element, pointed by data,
 * to the top of given stack.
 * Before pushing a new element, making sure the stack isn't
 * full is requiered. In the case of trying to push to a full stack,
 * or in case any of the pointers is pointing to NULL,
 * the behavior will be undefined.
 * Time complexity: O(1)
 *
 * @param:
 * stack_t *stack:	pointer to stack
 * void *data:		pointer to the element to be pushed
 *
 */
void StackPush(stack_t *stack, const void *data);


/* DESCRIPTION:
 * Function for popping the top element off given stack.
 * Before pupping off an element, making sure the stack isn't
 * empty is requiered. In the case of trying to pop an empty stack,
 * or in case the pointer is pointing to NULL,
 * the behavior will be undefined.
 * Time complexity: O(1)
 *
 * @param:
 * stack_t *stack:	pointer to stack
 *
 */
void StackPop(stack_t *stack);


/* DESCRIPTION:
 * Function for peeking at the element placed at the top of the stack,
 * In case the pointer is pointing to NULL,
 * the behavior will be undefined.
 * Time complexity: O(1)
 *
 * @param:
 * stack_t *stack:	pointer to stack
 *
 * @return:
 * Returns pointer to top element of the stack
 *
 */
void *StackPeek(const stack_t *stack);


/* DESCRIPTION:
 * Function for checking the capacity of stack.
 * In case the pointer is pointing to NULL,
 * the behavior will be undefined.
 * Time complexity: O(1)
 *
 * @param:
 * stack_t *stack:	pointer to stack
 *
 * @return:
 * Returns the capacity of the stack
 *
 */
size_t StackCapacity(const stack_t *stack);


/* DESCRIPTION:
 * Function for checking if stack is empty.
 * In case the pointer is pointing to NULL,
 * the behavior will be undefined.
 * Time complexity: O(1)
 *
 * @param:
 * stack_t *stack:	pointer to stack
 *
 * @return:
 * Returns 1 if stack is empty, or 0 if it's not
 *
 */
int StackIsEmpty(const stack_t *stack);


/* DESCRIPTION:
 * Function for checking the number of existing elements in the stack.
 * In case the pointer is pointing to NULL,
 * the behavior will be undefined.
 * Time complexity: O(1)
 *
 * @param:
 * stack_t *stack:	pointer to stack
 *
 * @return:
 * Returns the number of existing elements
 *
 */
size_t StackSize(const stack_t *stack);


#endif /* __ILRD_OL95_STACK_H__ */
