/******************************************************************************
 * Title:		linear_sorts
 * Description:	linear sorts functions
 * Author:		Omer Avioz	
 * Reviewer:	Amit Glazer
 * 
 * InfinityLabs OL95
 *****************************************************************************/

#include <stdio.h>
#include <assert.h>
#include "linear_sorts.h"
#include <stdlib.h>

static size_t MaxValueInArray(int *arr, size_t size)
{
	int max = arr[0];
	size_t index;
	for(index = 0; index < size; ++index)
	{
		max = ((max > arr[index]) ? max : arr[index]);
	}
	return max;
	
}

static size_t MinValueInArray(int *arr, size_t size)
{
	int min = arr[0];
	size_t index;
	for(index = 0; index < size; ++index)
	{
		min = ((min < arr[index]) ? min : arr[index]);
	}
	return min;
}


static void CountingRadixSort(int *arr, size_t size, int place)
{

	int *count_array = NULL;
	int *res_array = NULL;
	long index;

	assert(NULL != arr);

	count_array = calloc(10, sizeof(int));
	res_array = calloc(size, sizeof(int));
	
	for(index = 0; (size_t)index < size; ++index)
	{
		
		++(count_array[(arr[index] / place) % 10]); 
	}
	
	for(index = 1; index < 10; ++index)
	{
		count_array[index] += count_array[index - 1];
	}
	
	for(index = size -1; index >= 0; --index)
	{
		res_array[count_array[(arr[index] / place) % 10] - 1] = arr[index];
		--(count_array[(arr[index] / place) % 10]);
	}
	
	for(index = 0; (size_t)index < size; ++index)
	{
		arr[index] = res_array[index];
	}
	
	free(res_array); res_array = NULL;
	free(count_array);	count_array = NULL;
	
}

void CountingSort(int *arr, size_t size)
{
	size_t max_value, min_value , count_array_size, arr_idx, index;
	int *count_array = NULL;

	assert(NULL != arr);

	max_value = MaxValueInArray(arr, size);
	min_value = MinValueInArray(arr, size);
	count_array_size = max_value - min_value + 1;
	count_array = calloc((count_array_size), sizeof(int));
	arr_idx = 0;

	for(index = 0; index < size; ++index)
	{
		++(count_array[arr[index] - min_value]); 
	}

	for(index = 0;index < count_array_size; ++index)
	{
			
		while(count_array[index])
		{
			arr[arr_idx] = index + min_value;
			--(count_array[index]);
			++arr_idx;			
		}
		
	}
	
	free(count_array); count_array = NULL;

}

void RadixSort(int *arr, size_t size)
{
	size_t place, max_value;
	
	assert(NULL != arr);
	
	max_value = MaxValueInArray(arr, size);
	
	for(place = 1; (max_value/place) > 0; place *= 10)
	{
		CountingRadixSort(arr, size, place);
	}
	

}

