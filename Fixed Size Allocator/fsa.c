/********************************************
Title: Fixed Size Allocator
File name : fsa.c
Author : Omer Avioz
Reviewer : Dafna Kadosh Mahler 
Infinity Labs OL95	
*******************************************/

/* 				External Libraries
-------------------------------------------*/

#include "fsa.h"	/*fsa API's*/
#include <assert.h>	/*assert*/

#define FSA_SIZE sizeof(struct fsa)
#define SIZE_OF_WORD sizeof(size_t)
#define MEM_BLOCK_SIZE sizeof(struct mem_block)

typedef struct mem_block block_t;

struct fsa
{
	size_t next_free;		     
};


struct mem_block
{
    size_t next_free;
};

static size_t BlockSizeWithAlignment(size_t block_size)
{
	return block_size + (SIZE_OF_WORD - (block_size % SIZE_OF_WORD)) % SIZE_OF_WORD;
}

static size_t NumberOfBlocks(size_t total_bytes, size_t block_size_aligned)
{
	return ((total_bytes - FSA_SIZE) / block_size_aligned);
}
					 


fsa_t *FSAInit(void *segment, size_t total_bytes, size_t block_size)
{
	size_t block_size_aligned = BlockSizeWithAlignment(block_size);
    size_t blocks_i = 0;
    size_t i = 0;
    size_t blocks_num = NumberOfBlocks(total_bytes, block_size_aligned);
    block_t *block = NULL;   
    fsa_t *fsa = NULL;

    assert (NULL != segment);
    
    if (block_size_aligned + FSA_SIZE > total_bytes)
    {
    	return NULL;
    }

    fsa = (fsa_t*)segment;
    blocks_i = FSA_SIZE;
    fsa->next_free = blocks_i;

    for (; i < blocks_num; ++i)
    {
        block = (block_t *)((char *)fsa + blocks_i);
        blocks_i += block_size_aligned;
        block->next_free = blocks_i;
    }

	block->next_free = 0;
      
    return fsa;   
}


void *FSAAlloc(fsa_t *fsa)
{
	size_t next_block = 0;
	
	assert(NULL != fsa);
	
	if (0 == fsa->next_free) 
	{
		return NULL;
	}
	
	next_block = fsa->next_free;
	fsa->next_free = ((block_t *)((char *)fsa + fsa->next_free))->next_free;
	return ((char *)fsa + next_block);
}


void FSAFree(fsa_t *fsa, void *allocated_mem)
{
	size_t temp = 0;
	block_t *block = NULL;
	
	assert(NULL != fsa);
	
	if (NULL == allocated_mem) 
	{
		return;
	}
	
	temp = fsa->next_free;
	block = (block_t *)allocated_mem;
	fsa->next_free = (size_t)block - (size_t)fsa;
	block->next_free = temp;
}


size_t FSACountFree(const fsa_t *fsa)
{
	int count = 0;
	block_t *curr_block = NULL;
	assert(NULL != fsa);
	
	if (0 == fsa->next_free)
	{
		return 0;
	}
	
	curr_block = (block_t *)((char *)fsa + fsa->next_free);
	
	for (;(size_t *)curr_block != (size_t *)fsa; ++count)
	{
		curr_block = (block_t *)((char *)fsa + curr_block->next_free);	
	}
	
	return count;
}


size_t FSASuggestSize(size_t num_of_blocks, size_t block_size)
{
	return FSA_SIZE + (num_of_blocks * BlockSizeWithAlignment(block_size));
}




