/*******************************************************************************
*                  task - HEADER FILE        
* 												 		 
* Description: task functions.
* Worksheet: DS Priority Queue										 										 
* InfinityLabs OL95										 
*******************************************************************************/
/*---------------------------- Header Guard ----------------------------------*/

#ifndef __ILRD_OL95_TASK_H__
#define __ILRD_OL95_TASK_H__

/*-------------------------- HEADER FILES ------------------------------------*/
#include <stddef.h> /* size_t */
#include "uid.h"


/*------------------------- TYPEDEF ------------------------------------------*/
 
typedef int (*actionDListRemove_t)(const void *param);

typedef struct task task_t;


/* DESCRIPTION:
 * A function that creates a new priority pq.
 * Memory will be specially allocated.
 * In case of memory allocation failure, NULL will be returned.
 * In order to avoid memory leaks, the PQueueDestroy function is required at
 * end of use.
 *
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * cmp - the users compare function
 * const void *new_data - new data to be compared
 * const void *existing_data - existing data to be compared
 * RETURN VALUE:
 * pq_t * - pointer to new created pq, NULL if memory
 * allocation failed.
 */  
task_t *TaskCreate(time_t first_execution, size_t interval_in_sec, int(*action)(void *params), void *params);
									
 
/* DESCRIPTION:
 * A function that destroys a specified priority pq . 
 * Previously allocated memory will be freed.
 * All remaining data will be lost 
 *
 * Time complexity: O(n)
 *
 * PARAMETERS:
 * pq_t *pq - pointer to a pq to be 
 * destroyed
 *
 * (In case of pointer pointing to invalid pq, behavior is undefined)
 *
 * RETURN VALUE: 
 * no return value
 */
void TaskDestroy(task_t *task);


/* DESCRIPTION:
 * Function for getting the tasks UID
 * In case the pointer is pointing to NULL, the behavior will be undefined
 * Time complexity: O(1) 
 *
 * @param:
 * const task_t *task:        pointer to task
 *
 * @return:
 * Returns tasks UID
 */

ilrd_uid_t TaskGetUID(const task_t *task);


/* DESCRIPTION:
 * Function for runnuing a given tasks.
 * In case queue is pointing to an invalid queue, or any of the pointers
 * is pointing to NULL, the behavior will be undefined
 * Time complexity: O(1) 
 *
 * @param:
 * const task_t *task:        pointer to task to be run
 *
 * @return:
 * Returns 1 if ran, or 0 if not
 */
int TaskRun(const task_t *task);


/* DESCRIPTION:
 * Function for setting the tasks first_execution.
 * In case the pointer is pointing to NULL,
 * the behavior will be undefined
 * Time complexity: O(1) 
 *
 * @param:
 * const task_t *task:		pointer to task to be frequency set
 *
 */
void TaskSetNextExecution(task_t *task, size_t next_execution);


/* DESCRIPTION:
 * Function for getting the tasks frequency_in_sec
 * In case the pointer is pointing to NULL, the behavior will be undefined
 * Time complexity: O(1) 
 *
 * @param:
 * const task_t *task:		pointer to task
 *
 * @return:
 * Returns size_t frequency_in_sec
 */
size_t TaskGetFrequencyInSec(const task_t *task);


/* DESCRIPTION:
 * Function for getting the tasks first_execution
 * In case the pointer is pointing to NULL, the behavior will be undefined
 * Time complexity: O(1) 
 *
 * @param:
 * const task_t *task:		pointer to task
 *
 * @return:
 * Returns time_t first_execution
 */
size_t TaskGetFirstExecution(const task_t *task);

#endif /* __ILRD_OL95_TASK_H */



