/*******************************************************************************
*                  DS - SCHEDULER - HEADER FILE        
* 												 		 
* Description: API of Scheduler functions
* Worksheet: Scheduler										 
* Date: 15.10.2020										 
* InfinityLabs OL95										 
*******************************************************************************/
/*---------------------------- Header Guard ----------------------------------*/

#ifndef __ILRD_OL95_SCHEDULER_H__
#define __ILRD_OL95_SCHEDULER_H__

/*-------------------------- HEADER FILES ------------------------------------*/
#include <stddef.h> /* size_t */
#include "uid.h" /* uid header */
/*------------------------- TYPEDEF ------------------------------------------*/
 
typedef struct scheduler sched_t;

 
/* in c file

#include "pq.h"
#include "sched.h"
#include "task.h"

struct scheduler
{
	pq_t *pq;
	task_t *current_task;
	int is_running;
};

*/

/* DESCRIPTION:
 * A function that creates a new scheduler.
 * Memory will be specially allocated.
 * In case of memory allocation failure, NULL will be returned.
 * In order to avoid memory leaks, the SchedDestroy function is required at
 * end of use.
 *
 * Time complexity: O(1)
 *
 * RETURN VALUE:
 * sched_t * - pointer to new created sched, NULL if memory
 * allocation failed.
 */ 
 
sched_t *SchedCreate(void);
/*----------------------------------------------------------------------------*/
/* DESCRIPTION:
 * A function that destroys a specified scheduler . 
 * Previously allocated memory will be freed.
 * All remaining tasks will be lost 
 *
 * Time complexity: O(n)
 *
 * PARAMETERS:
 * sched_t *sched - pointer to a sched to be 
 * destroyed
 *
 * (In case of pointer pointing to invalid sched, behavior is undefined)
 *
 * RETURN VALUE: 
 * no return value
 */
 
void SchedDestroy(sched_t *sched);
/*----------------------------------------------------------------------------*/
/* DESCRIPTION:
 * A function that creates a new Sched element that holds  
 * specified task and adds it to the Sched considering its priority. 
 * Memory will be allocated for new Sched element.
 *
 * Time complexity: O(n) 
 *
 * PARAMETERS:
 * sched_t *Sched -	pointer to Sched to be added to. 
 * size_t first_execution - first time to execute the task
 * size_t frequency_in_sec - frequency of the function returns
 * *action - the function to preform return 0 if function should return
 *   and 1 if not) 
 * params - parameter for the action function 
 *
 *(In case of pointers pointing to invalid Sched or task, behavior is undefined)
 *
 * RETURN VALUE:
 * ilrd_uid_t - unique identifier of task on success .
 */
ilrd_uid_t SchedAddTask(sched_t *sched, time_t first_execution,
		size_t frequency_in_sec, int(*action)(void *params), void *params);
/*----------------------------------------------------------------------------*/
/* DESCRIPTION:
 * A function that erase a specific task.
 * 
 * Time complexity: O(n)
 *
 * PARAMETERS:
 * const sched_t *sched - pointer to a sched.
 * ilrd_uid_t task_id - the specific task id 
 * 
 *(In case of pointer pointing to invalid variable, behavior is undefined)
 *
 * RETURN VALUE:
 * no return value
 */
void SchedRemoveTask(sched_t *sched, ilrd_uid_t task_id);
/*----------------------------------------------------------------------------*/
/* DESCRIPTION:
 * A function that returns current number of elements in a Sched. 
 *
 * Time complexity: O(n)
 *
 * PARAMETERS:
 * sched_t *Sched - pointer to a sched. 
 *
 * (In case of pointer pointing to invalid sched, behavior is undefined)
 *
 * RETURN VALUE:
 * size_t - current number of tasks in a sched.
 */
size_t SchedSize(const sched_t *sched);
/*----------------------------------------------------------------------------*/
/* DESCRIPTION:
 * A function that checks if a Sched is empty or not.
 * 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * const sched_t *sched - pointer to a sched.
 *
 * (In case of pointer pointing to invalid variable, behavior is undefined)
 *
 * RETURN VALUE:
 * int - one if sched is empty, zero if sched is not empty.
 */
int SchedIsEmpty(const sched_t *sched);
/*----------------------------------------------------------------------------*/
/* DESCRIPTION:
 * A function that clear the queue to be empty.
 * 
 * Time complexity: O(n)
 *
 * PARAMETERS:
 *  sched_t *sched - pointer to a sched.
 * 
 * (In case of pointer pointing to invalid variable, behavior is undefined)
 *
 * RETURN VALUE:
 * no return value.
 */
void SchedClear(sched_t *sched);
/*----------------------------------------------------------------------------*/
/* DESCRIPTION:
 * A function that run the tasks till is empty or stoped by SchedStop().
 * 
 * Time complexity: O(n)
 *
 * PARAMETERS:
 *  sched_t *sched - pointer to a sched.
 * 
 * (In case of pointer pointing to invalid variable, behavior is undefined)
 *
 * RETURN VALUE:
 * int - zero if succeeded, non-zero if failed.
 */
int SchedRun(sched_t *sched);
/*----------------------------------------------------------------------------*/
/* DESCRIPTION:
 * A function that stops the execution of scheduler tasks.
 * 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 *  sched_t *sched - pointer to a sched.
 * 
 * (In case of pointer pointing to invalid variable, behavior is undefined)
 *
 * RETURN VALUE:
 * no return value.
 */
void SchedStop(sched_t *sched);
/*----------------------------------------------------------------------------*/
#endif /*__ILRD_OL95_SCHEDULER_H___*/
