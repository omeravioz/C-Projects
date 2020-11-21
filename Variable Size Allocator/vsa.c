/******************************************************************************
 * Title:		vsa.c
 * Description:	Implementations of vsa functions
 * Author:	Omer Avioz	
 * Reviewer: Yoav Porag
 * 
 * InfinityLongAbs OL95
 *****************************************************************************/
#include <assert.h> /* assert() */  
#include <stdlib.h> /* malloc(), free() */
#include "vsa.h" /* vsa function */


/**********************************vsa*************************************/
#ifndef NDEBUG
#define DEBUG_ONLY(code) code
#else
#define DEBUG_ONLY(code)
#endif

#define VSA_SIZE sizeof(vsa_t)
#define BLOCK_H_SIZE sizeof(block_h_t)
#define SIZE_OF_WORD sizeof(size_t)


/**********************************vsa*************************************/

typedef struct block_header block_h_t;

struct vsa
{
	size_t total_size; 
};

struct block_header
{
	long block_size; 
DEBUG_ONLY(
	vsa_t *owner;
)
};


static block_h_t* GetBlockHAddress(void *block_h)
{
	return (block_h_t *)((char *)block_h - BLOCK_H_SIZE);
}

static long ExtractBlockSize(void *block_h)
{
	return ((block_h_t *)block_h)->block_size;
}

static size_t ExtractTotalSize(void *vsa)
{
	return ((vsa_t *)vsa)->total_size;
}

static long LongAbs(long num)
{
	if(num < 0)
	{
		return (num * (-1));
	}
	return num;
}

static size_t GetBlockSizeWithAlignment(size_t block_size)
{
	return block_size + (SIZE_OF_WORD - (block_size % SIZE_OF_WORD)) % SIZE_OF_WORD;
}

static block_h_t *GetFirstBlockHeader(const vsa_t *vsa)
{
	assert(NULL != vsa);

	return (block_h_t *)((char *)vsa + VSA_SIZE);
}

static block_h_t* GetNextBlockH(block_h_t* curr_block_h)
{
	assert(NULL != curr_block_h);
	return (block_h_t *)((char *)curr_block_h +
			BLOCK_H_SIZE + LongAbs(ExtractBlockSize(curr_block_h)));
}

static size_t AddToFreeMemoryCount(block_h_t* runner, int *is_first)
{
	size_t ans = LongAbs((ExtractBlockSize(runner)) * (-1));
	assert(NULL != is_first);
	if(*is_first == 0)
	{
		ans += BLOCK_H_SIZE;
		
	}
	*is_first = 0;
	return ans;
}


/*******************************************************************************
                            VSAInit                             
*******************************************************************************/
vsa_t *VSAInit(void *segment, size_t segment_size)
{
	vsa_t *vsa = NULL;
	block_h_t *block = NULL; 
	
	assert(NULL != segment);
	if(segment_size < VSA_SIZE + BLOCK_H_SIZE)
	{
		return NULL;
	}
	
	vsa = (vsa_t *)segment;
	vsa->total_size = segment_size - (segment_size % SIZE_OF_WORD);
	
	block = (block_h_t *)((char *)segment + VSA_SIZE);
	block->block_size = ((vsa->total_size) - VSA_SIZE - BLOCK_H_SIZE) * (-1);
	DEBUG_ONLY(
	block->owner = vsa;
	)
	
	return vsa;
}

/*******************************************************************************
                            VSAAlloc                             
*******************************************************************************/
void *VSAAlloc(vsa_t *vsa, size_t requested_size)
{
	size_t end_of_segment = 0;
	size_t continuous_free_memory = 0;
	block_h_t *runner = NULL;
	block_h_t *runner_first_empty = NULL;
	int is_first = 1;
	
	assert(NULL != vsa);
	
	requested_size = GetBlockSizeWithAlignment(requested_size);
	end_of_segment = (size_t)vsa + ExtractTotalSize((vsa_t *)vsa);
	runner = GetFirstBlockHeader(vsa);
	runner_first_empty = runner;
	
	for(; continuous_free_memory < GetBlockSizeWithAlignment(requested_size) &&
			(size_t )runner < end_of_segment; 
			runner = GetNextBlockH(runner)) 
	{
			if(ExtractBlockSize(runner) < 0)
			{
				continuous_free_memory += AddToFreeMemoryCount(runner, &is_first);
			}	
			else
			{
				continuous_free_memory = 0;
				runner_first_empty = GetNextBlockH(runner);
			}
	}

	if(continuous_free_memory >= GetBlockSizeWithAlignment(requested_size))
	{
		runner_first_empty->block_size = GetBlockSizeWithAlignment(requested_size);

		if(continuous_free_memory - GetBlockSizeWithAlignment(requested_size) >=
		 (BLOCK_H_SIZE + SIZE_OF_WORD))
		{
			block_h_t *next_free = GetNextBlockH(runner_first_empty);
			DEBUG_ONLY(
			next_free->owner = vsa;
			)
			next_free->block_size = (continuous_free_memory -
		 	(GetBlockSizeWithAlignment(requested_size) + BLOCK_H_SIZE)) * (-1);
			
		}
		else
		{
			runner_first_empty->block_size += 
			(continuous_free_memory - GetBlockSizeWithAlignment(requested_size));
		}
		
		return ((char *)runner_first_empty + BLOCK_H_SIZE);
	}

	return NULL;
}

/*******************************************************************************
                            VSAFree                             
*******************************************************************************/
void VSAFree(vsa_t *vsa, void *allocated_mem)
{
	assert(NULL != vsa);
	assert(vsa == GetBlockHAddress(allocated_mem)->owner);

	if(NULL != allocated_mem &&
	   ExtractBlockSize((char *)allocated_mem - BLOCK_H_SIZE ) > 0)
	{
		(GetBlockHAddress(allocated_mem))->block_size *= (-1);

	}
}

/*******************************************************************************
                            VSALargestBlockAvailable                             
*******************************************************************************/
size_t VSALargestBlockAvailable(const vsa_t *vsa)
{
	size_t end_of_segment = 0;
	size_t largest_block = 0;
	size_t temp_max = 0;
	block_h_t *runner = NULL;
	
	assert(NULL != vsa);
	
	end_of_segment = (size_t)vsa + ExtractTotalSize((vsa_t *)vsa);
	runner = GetFirstBlockHeader(vsa);
	
	for(; (size_t )runner < end_of_segment; runner = GetNextBlockH(runner)) 
	{

			if(ExtractBlockSize(runner) < 0)
			{
				temp_max += (ExtractBlockSize(runner) * (-1)) + BLOCK_H_SIZE;
			}
			else if(largest_block < temp_max)
			{	
				largest_block = temp_max - BLOCK_H_SIZE;
				temp_max = 0;
			} 
	}
	if(largest_block < temp_max)
	{
		largest_block = temp_max - BLOCK_H_SIZE;
	}
	
	return largest_block;	
}



