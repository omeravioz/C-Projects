/****************************************************************************
*                  DS - Task - HEADER FILE        
* 												 		 
* Description: API of Task functions
* Worksheet: taskuler										 
* Date: 15.10.2020										 
* InfinityLabs OL95										 
****************************************************************************/
/*---------------------------- Header Guard -------------------------------*/

#ifndef __ILRD_OL95_TASK_H__
#define __ILRD_OL95_TASK_H__

/*-------------------------- HEADER FILES ---------------------------------*/
#include <stddef.h> /* size_t */
#include "uid.h" /* uid header */
/*------------------------- TYPEDEF ---------------------------------------*/

typedef struct task task_t;

/* in c file

struct task
{
	ilrd_uid_t uid;
	size_t frequency_in_sec;
	int (*action)(void *params);
	time_t time;
	void *params;
    
};
*/

/* DESCRIPTION:
 * A function that creates a new task.
 * Memory will be specially allocated.
 * In case of memory allocation failure, NULL will be returned.
 * In order to avoid memory leaks, the TaskDestroy function is required at
 * end of use.
 *
 * Time complexity: O(1)
 *
 * RETURN VALUE:
 * task_t * - pointer to new created task, NULL if memory allocation failed.
 */
task_t *TaskCreate(time_t first_execution, size_t frequency_in_sec, int(*action)(void *params), void *params);

/* DESCRIPTION:
 * A function that destroys a specified taskuler . 
 * Previously allocated memory will be freed.
 * All remaining tasks will be lost 
 *
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * task_t *task - pointer to a task to be destroyed
 *
 * (In case of pointer pointing to invalid task, behavior is undefined)
 *
 * RETURN VALUE: 
 * no return value
 */
void TaskDestroy(task_t *task);

/* DESCRIPTION:
* A function that run the tasks till is empty or stoped by taskStop().
* 
* Time complexity: O(1)
*
* PARAMETERS:
*  task_t *task - pointer to a task.
*
* (In case of pointer pointing to invalid variable, behavior is undefined)
*
* RETURN VALUE:
* 
* return 0 if function should return and 1 if not.
*/
int RunTask(task_t *task);

/* DESCRIPTION:
* A function that return task UID.
* 
* Time complexity: O(1)
*
* PARAMETERS:
*  task_t *task - pointer to a task.
*
* (In case of pointer pointing to invalid variable, behavior is undefined)
*
* RETURN VALUE:
* 
* return UID.
*/

ilrd_uid_t GetUID(task_t *task);

/* DESCRIPTION:
* A function that return task time.
* 
* Time complexity: O(1)
*
* PARAMETERS:
*  task_t *task - pointer to a task.
*
* (In case of pointer pointing to invalid variable, behavior is undefined)
*
* RETURN VALUE:
* 
* return time.
*/

time_t GetTaskTime(task_t *task);

time_t GetTaskExecution(task_t *task);

int TaskIsMatch(const void *task, const void *uid);

void SetTaskTime(task_t *task);

/*task_t *TaskStop(task_t *task);*/

/*int Stop(void *params);*/


#endif /* __ILRD_OL95_TASK_H__ */


