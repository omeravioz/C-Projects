/******************************************************************************
 * Title:		task.c
 * Description:	Implementations of task functions
 * Author:		Omer Avioz
 * Reviewer:	Yonatan Cohen	
 * 
 * InfinityLabs OL95
*****************************************************************************/

/* 				External Libraries
-------------------------------------------*/

#include "task.h"	/* task API's*/
#include <assert.h>	/* assert*/
#include <stdlib.h> /* malloc, free */

static const int max_priority = 7;
static int curr_priority = 0;

struct task
{
	ilrd_uid_t uid;
	int(*action)(void *params);
	size_t frequency_in_sec;
	time_t first_execution;
	void *params;
};



task_t *TaskCreate(time_t first_execution, size_t frequency_in_sec, int(*action)(void *params), void *params)
{
	task_t *new_task = (task_t *)malloc(sizeof(task_t));
	
	assert(NULL != action);

	
	if(NULL == new_task)
	{
		return NULL;
	}
	
	new_task->uid = UIDCreate();
	if(UIDIsSame(BAD_UID,new_task->uid))
	{
		free(new_task);
		return NULL;
	}
	
	new_task->action = action;
	new_task->params = params;
	new_task->frequency_in_sec = frequency_in_sec;
	new_task->first_execution = first_execution;
	
	curr_priority = (curr_priority + 1) % max_priority;
	
	return new_task;
	
}

void TaskDestroy(task_t *task)
{
	assert(NULL != task);
	
	free(task); task = NULL;
}


int TaskRun(const task_t *task)
{
	return task->action(task->params);
	
}

ilrd_uid_t TaskGetUID(const task_t *task)
{
	assert(NULL != task);
	
	return task->uid;
}

void TaskSetNextExecution(task_t *task, size_t next_execution)
{
	assert(NULL != task);
	
	task->first_execution += next_execution;
}

size_t TaskGetFrequencyInSec(const task_t *task)
{
	return task->frequency_in_sec;
}

size_t TaskGetFirstExecution(const task_t *task)
{
	return task->first_execution;
}











