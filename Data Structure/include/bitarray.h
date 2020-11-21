/**********************************************************************************************
*                              	  DS - Bit Array                                       *
* 												 *
* Description: implementations of bit array functions.					 *
* Worksheet: 1											 *
* date: 24.09.2020										 *
* InfinityLabs OL95										 *
**********************************************************************************************/

/*----------------------------------- Header Guard ------------------------------------------*/
#ifndef _ILRD_OL95_BIT_ARRAY_H_
#define _ILRD_OL95_BIT_ARRAY_H_

/*------------------------------ Functions declarations -------------------------------------*/
typedef unsigned long bitarr_t;

/* DESCRIPTION: Function that will set all bits on. */
bitarr_t BitArraySetAll(bitarr_t bit_array);


/* DESCRIPTION: Function that will set all bits off. */
bitarr_t BitArrayResetAll(bitarr_t bit_array);


/* DESCRIPTION: Function that will convert the bits to string. */
char *BitArrayToString(bitarr_t bit_array, char *str);


/* DESCRIPTION: Function that will set a specific bit on. */
bitarr_t BitArraySetOn(bitarr_t bit_array, unsigned int index);


/* DESCRIPTION: Function that will set a specific bit off. */
bitarr_t BitArraySetOff(bitarr_t bit_array, unsigned int index);


/* DESCRIPTION: Function that will set a specific bit on or off as the user decides. */
bitarr_t BitArraySetBit(bitarr_t bit_array, unsigned int index, unsigned int set_state);


/* DESCRIPTION: Function that will inform us about bit's value. */
unsigned int BitArrayGetVal(bitarr_t bit_array, unsigned int index);


/* DESCRIPTION: Function that will change every bit. */
bitarr_t BitArrayFlip(bitarr_t bit_array, unsigned int index);


/* DESCRIPTION: Function that will reverse all bits. */
bitarr_t BitArrayMirror(bitarr_t bit_array);


/* DESCRIPTION: Function that will rotate right. */
bitarr_t BitArrayRotRight(bitarr_t bit_array, unsigned int rot_num);


/* DESCRIPTION: Function that will rotate left. */
bitarr_t BitArrayRotLeft(bitarr_t bit_array, unsigned int rot_num);


/* DESCRIPTION: Function that will counts on bits. */
unsigned int BitArrayCountOn(bitarr_t bit_array);


/* DESCRIPTION: Function that will counts off bits. */
unsigned int BitArrayCountOff(bitarr_t bit_array);

#endif /*_ILRD_OL95_BIT_ARRAY_H_*/
