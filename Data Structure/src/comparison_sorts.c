#include "comparison_sorts.h"
#include <assert.h>

static void Swap(int *i, int *j)
{
	int temp = *i;
	*i = *j;
	*j = temp;
}

void BubbleSort(int arr[], size_t size)
{
	
	size_t i = 0;
	
	assert(NULL != arr);
	
	for(; i < size - 1; ++i)
	{
		size_t j = 0;
		int is_swapped = 0;
		for(; j < (size - (i + 1)) ; ++j)
		{
			if(arr[j] > arr[j+1])
			{
				Swap(&arr[j], &arr[j+1]);
				is_swapped = 1;
			}
		}
		
		if(0 == is_swapped)
		{
			break;
		}
	}
}

void InsertionSort(int arr[], size_t size)
{
	size_t i = 1;
	
	assert(NULL != arr);
	
	for(; i < size; ++i)
	{
		long j = i -1;
		int temp = arr[i];
		for(;j >= 0 && temp < arr[j]; --j)
		{
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = temp;
	}
}

void SelectionSort(int arr[], size_t size)
{
	size_t i, j;
	
	assert(NULL != arr);
	
	for(i = 0; i < size-1; ++i)
	{
		size_t min_index = i;
		for(j = i + 1; j < size; ++j)
		{
			min_index = ((arr[min_index] < arr[j]) ? (min_index) : (j));
		}
		if(i != min_index)
		{
			Swap(&arr[i], &arr[min_index]);
		}
	}
}

