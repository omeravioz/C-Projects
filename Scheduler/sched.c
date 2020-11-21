/******************************************************************************
 * Title:		sched.c
 * Description:	Implementations of sched functions
 * Author:		Omer Avioz
 * Reviewer:	Yonatan Cohen	
 * 
 * InfinityLabs OL95
*****************************************************************************/

/* 				External Libraries
-------------------------------------------*/
#include "pq.h"		/*pq API's*/
#include "sched.h"	/*sched API's*/
#include "task.h"	/*task API's*/
#include <assert.h>	/* assert*/
#include <stdlib.h> /* malloc, free */



/**********************************sched************************************/
struct scheduler
{
	pq_t *pq;
	task_t *current_task;
	int is_running;
};

static int FrequencyCmp(const void *new_task, const void *existing_task);
static int IsUIDMatch(const void *data, const void *params);
static void SleepTillNextExec(sched_t *sched);
static int SetNextExecutionOfTask(sched_t *sched);


/*******************************************************************************
                            SchedCreate                             
*******************************************************************************/
sched_t *SchedCreate(void)
{
	sched_t *new_sched = (sched_t*) malloc (sizeof(sched_t));
	
	if(NULL == new_sched)
	{
		return NULL;
	}
	
	new_sched->pq = PQCreate(FrequencyCmp);
	if(NULL == new_sched->pq)
	{
		free(new_sched);
		return NULL;
	}
	
	new_sched->is_running = 0;
	new_sched->current_task = NULL;
	
	return new_sched;
}

/*******************************************************************************
                            SchedDestroy                             
*******************************************************************************/

void SchedDestroy(sched_t *sched)
{
	assert(NULL != sched);
	
	SchedClear(sched);
	PQDestroy(sched->pq);
	free(sched); sched = NULL;
}

/*******************************************************************************
                            SchedAddTask                             
*******************************************************************************/
ilrd_uid_t SchedAddTask(sched_t *sched, 
						time_t first_execution, 
						size_t frequency_in_sec,
						int(*action)(void *params),
					    void *params)
{
	task_t *new_task = NULL;
	
	assert(NULL != sched);
	assert(NULL != action);
	
	new_task = TaskCreate(first_execution, frequency_in_sec, action, params);
	if(NULL == new_task)
	{
		return BAD_UID;
	}
	
	if( 1 == PQEnqueue(sched->pq, new_task))
	{
		TaskDestroy(new_task);
		return BAD_UID;
	}
	
	return TaskGetUID(new_task);
	
}

/*******************************************************************************
                            SchedRemoveTask                             
*******************************************************************************/
void SchedRemoveTask(sched_t *sched, ilrd_uid_t task_id)
{
	task_t *task_to_destroy = NULL;
	assert(NULL != sched);
	if(NULL != sched->current_task && IsUIDMatch(&task_id, sched->current_task))
	{
		TaskDestroy(sched->current_task);
		sched->current_task = NULL;
	}
	else
	{
		task_to_destroy = (task_t *)PQErase(sched->pq, &IsUIDMatch , &task_id);
	 		if(task_to_destroy != NULL)
	 		{
				TaskDestroy(task_to_destroy);
				task_to_destroy = NULL;
			}
	}
}

/*******************************************************************************
                            SchedSize                             
*******************************************************************************/
size_t SchedSize(const sched_t *sched)
{
	assert(NULL != sched);
	
	return PQSize(sched->pq) + (sched->current_task != NULL);
}

/*******************************************************************************
                            SchedIsEmpty                             
*******************************************************************************/
int SchedIsEmpty(const sched_t *sched)
{
	assert(NULL != sched);
	
	return (PQIsEmpty(sched->pq)) && (sched->current_task == NULL);
}

/*******************************************************************************
                            SchedClear                             
*******************************************************************************/
void SchedClear(sched_t *sched)
{
	assert(NULL != sched);
	
	if(NULL != sched->current_task)
	{
		TaskDestroy(sched->current_task);
		sched->current_task = NULL;
	}
	
	while(!SchedIsEmpty(sched))
	{
		TaskDestroy((task_t *)PQDequeue(sched->pq));
	}
	
}

/*******************************************************************************
                            SchedRun                             
*******************************************************************************/
int SchedRun(sched_t *sched)
{
	int sched_res = 0;
	
	assert(NULL != sched);
	
	sched->is_running = 1;
	
	while(!SchedIsEmpty(sched) && sched->is_running)
	{
		int task_run_res = 0;
		
		SleepTillNextExec(sched);
		
		sched->current_task = (task_t *)PQDequeue(sched->pq);
	
		task_run_res = TaskRun(sched->current_task);
		if(NULL == sched->current_task)
		{
			continue;
		}
		
		if(0 == task_run_res)
		{
			sched_res = SetNextExecutionOfTask(sched);	
		}
		
		else
		{
			TaskDestroy(sched->current_task);	
		}
		
		sched->current_task = NULL;
	}

	sched->is_running = 0;

	return sched_res;

}

/*******************************************************************************
                            SchedStop                             
*******************************************************************************/
void SchedStop(sched_t *sched)
{
	assert(NULL != sched);
	
	((sched_t *)sched)->is_running = 0;
}


static int FrequencyCmp(const void *new_task, const void *existing_task)
{
	assert(NULL != new_task);
	assert(NULL != existing_task);

	if((TaskGetFirstExecution((task_t *)new_task)) < (TaskGetFirstExecution((task_t *)existing_task)))
	{
		return 1;

	}
	
	if((TaskGetFirstExecution((task_t *)new_task)) > (TaskGetFirstExecution((task_t *)existing_task)))
	{
		return -1;

	}
	
	return 0;
	
}

static int IsUIDMatch(const void *data, const void *params)
{
	assert(NULL != data);
	assert(NULL != params);
	
	return UIDIsSame(*(ilrd_uid_t *)data, TaskGetUID((task_t *)params));
}

static void SleepTillNextExec(sched_t *sched)
{
		time_t curr_time = time(NULL);
		time_t next_exec = TaskGetFirstExecution((task_t *)(PQPeek(sched->pq)));
		while(next_exec > curr_time)
		{
			sleep(difftime(next_exec, curr_time));
			curr_time = time(NULL);
		}
}

static int SetNextExecutionOfTask(sched_t *sched)
{
			int enqueue_res = 0;
			TaskSetNextExecution(sched->current_task,
								 TaskGetFrequencyInSec(sched->current_task));
			enqueue_res = PQEnqueue(sched->pq, sched->current_task);

			if(enqueue_res)
			{
				TaskDestroy(sched->current_task);
				sched->is_running = 0;
				 return 1;
			}
			
			return 0;	
}

