/*********	***********************************
File name : Q9.c
Author : Omer Avioz
Reviewer : Ella Itzhak
Infinity Labs OL95	
*******************************************/

/* 				External Libraries
-------------------------------------------*/
#include "bitarray.h"
#include <stdio.h>	/* printf*/
#include <assert.h>	/* assert*/
#include <limits.h> /* CHAR_BIT */


/* 			Definitions
-------------------------------------------*/
#define LONG_BIT_SIZE (sizeof(bitarr_t) * CHAR_BIT)


/*			Functions
------------------------------------------*/

bitarr_t BitArraySetAll(bitarr_t bit_array)
{
	return (bit_array | 0xffffffffffffffff);
}


bitarr_t BitArrayResetAll(bitarr_t bit_array)
{
	return (bit_array & 0x0000000000000000);
}


char *BitArrayToString(bitarr_t bit_array, char *str)
{
	int count = LONG_BIT_SIZE;
	char *endptr = str + LONG_BIT_SIZE;
	
	assert(NULL != str);
	
	*endptr = '\0';
	--endptr;
	for(; count > 0 ; --count)
	{
		*endptr = ('0' + (bit_array % 2));
		bit_array >>= 1;
		--endptr;
		
	}
	/*printf("%s\n", str);*/
	
	return str;
}


bitarr_t BitArraySetOn(bitarr_t bit_array, unsigned int index)
{
	assert(63 >= index);	
		
	return (bit_array | ((bitarr_t)1 << index));

}


bitarr_t BitArraySetOff(bitarr_t bit_array, unsigned int index)
{
	assert(63 >= index);	

	return (bit_array & ~((bitarr_t)1 << index));
}


bitarr_t BitArraySetBit(bitarr_t bit_array, unsigned int index, unsigned int set_state)
{
	assert(63 >= index);	
	
	if( 1 == set_state)
	{	
		return BitArraySetOn(bit_array,index);
	}
	
	else if ( 0 == set_state)
	{
		return BitArraySetOff(bit_array,index);
	}
	
	else
	{
		return bit_array;
	}

}


unsigned int BitArrayGetVal(bitarr_t bit_array, unsigned int index)
{
	assert(63 >= index);	
	
	return (bit_array >> index & (bitarr_t)1);
}


bitarr_t BitArrayFlip(bitarr_t bit_array, unsigned int index)
{
	assert(63 >= index);	
	
	return (bit_array ^ ((bitarr_t)1 << index));
}


bitarr_t BitArrayMirror(bitarr_t bit_array)
{
    bit_array = ((bit_array & 0x5555555555555555) << 1) | ((bit_array & 0xAAAAAAAAAAAAAAAA) >> 1); 
    bit_array = ((bit_array & 0x3333333333333333) << 2) | ((bit_array & 0xCCCCCCCCCCCCCCCC) >> 2);
    bit_array = ((bit_array & 0x0F0F0F0F0F0F0F0F) << 4) | ((bit_array & 0xF0F0F0F0F0F0F0F0) >> 4); 
    bit_array = ((bit_array & 0x00FF00FF00FF00FF) << 8) | ((bit_array & 0xFF00FF00FF00FF00) >> 8); 
    bit_array = ((bit_array & 0x0000FFFF0000FFFF) << 16) | ((bit_array & 0xFFFF0000FFFF0000) >> 16); 
    bit_array = ((bit_array & 0x00000000FFFFFFFF) << 32) | ((bit_array & 0xFFFFFFFF00000000) >> 32);
	return bit_array;
}


bitarr_t BitArrayRotRight(bitarr_t bit_array, unsigned int rot_num)
{
	bitarr_t right;

	assert(63 >= rot_num);	
	
	right = bit_array << ((unsigned int)(LONG_BIT_SIZE) - rot_num);

	return ((right) | (bit_array >> rot_num));
}


bitarr_t BitArrayRotLeft(bitarr_t bit_array, unsigned int rot_num)
{
	bitarr_t left;
	
	assert(63 >= rot_num);
	
	left = bit_array >> ((unsigned int)(LONG_BIT_SIZE) - rot_num);
		
	return ((left) | (bit_array << rot_num));	
}

unsigned int BitArrayCountOn(bitarr_t bit_array)
{
	int bit_count = 0;
	while(bit_array != 0)
	{
		if(bit_array & 1)
		{
			++bit_count;
		}
		bit_array >>= 1;
	}
	return bit_count;
}


unsigned int BitArrayCountOff(bitarr_t bit_array)
{

	return (LONG_BIT_SIZE - BitArrayCountOn(bit_array));

}


