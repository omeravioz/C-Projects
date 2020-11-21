
#ifndef _UTILITIES_H
#define _UTILITIES_H

/*---------------------------------------------------------------*/
/* Testing macro */ 
#define TEST(condition, func_name) ((1) == (condition))?\
                                    printf("%s:\t\x1b[32m SUCCESS \x1b[0m | Line: %d\n", #func_name, __LINE__) : \
                                    printf("%s:\t\x1b[31m FAILURE \x1b[0m | Line: %d\n", #func_name, __LINE__)

/* Sub_testing macro */ 
#define SUB_TEST(string, condition) printf(string); condition ? printf("Success\n") : printf("Failed. Test line:%d\n", __LINE__);

#define SUCCESS (0)
/*---------------------------------------------------------------*/

/* Sending errors macro using errno (use in the case of error: perrno(name of function)) */
#ifndef NDEBUG
	#include <stdio.h>	/* perror() */
    #define ERR_PRINT(func_name) perror(__FILE__ " - " #func_name)
	#define CreateSlIterIMP(diter, sortedl) CreateSlIterIMP(diter, sortedl)

#else
    #define ERR_PRINT(func_name)
	#define CreateSlIterIMP(diter, sortedl) CreateSlIterIMP(diter)

#endif	/* NDEBUG		*/

/*---------------------------------------------------------------*/
/* macros for checking success of malloc */
#define MALLOC_CHECK(param, func_name) if (NULL == param)\
	{\
		ERR_PRINT(func_name);\
		return NULL;\
	}

#define MALLOC_CHECK_FREE(param, func_name, free_param) if (NULL == param)\
	{\
		free(free_param);\
		free_param = NULL;\
		ERR_PRINT(func_name);\
		return NULL;\
	}

#define MALLOC_CHECK_TWO_FREE(param, func_name, free_param, free_param2) if (NULL == param)\
    {\
        free(free_param);\
        free_param = NULL;\
        free(free_param2);\
        free_param2 = NULL;\
        ERR_PRINT(func_name);\
        return NULL;\
    }

#define MALLOC_CHECK_RETURN(param, func_name, to_return) if (NULL == param)\
	{\
		ERR_PRINT(func_name);\
		return to_return;\
	}

#define MALLOC_CHECK_VALUE_NO_STOP(param, func_name, value) if (value == param)\
	{\
		ERR_PRINT(func_name);\
	}


#define MALLOC_CHECK_INT_RETURN(param, func_name) if (0 != param)\
	{\
		ERR_PRINT(func_name);\
		return 1;\
	}

#define MALLOC_CHECK_NO_RETURN(param, func_name) if (NULL == param)\
	{\
		ERR_PRINT(func_name);\
		return;\
	}

#define MALLOC_CHECK_FREE_NO_RETURN(param, free_param, func_name) if (NULL == param)\
	{\
		ERR_PRINT(func_name);\
		free(free_param);\
		return;\
	}

#define MALLOC_CHECK_TWO_FREE_NO_RETURN(param, free_param, free_param2, func_name) if (NULL == param)\
	{\
		ERR_PRINT(func_name);\
		free(free_param);\
        free_param = NULL;\
		free(free_param2);\
        free_param2 = NULL;\
		return;\
	}
	
/* Macro for checking a success of a function by its return value, if fails - ends the function without a return value */
#define SUCCESS_CHECK_NO_RETURN(back_value) if (SUCCESS != back_value)\
	{\
		return;\
	}\

#define SUCCESS_CHECK_RETURN(back_value) if (NULL == back_value)\
	{\
		return NULL;\
	}\

/*---------------------------------------------------------------*/


/* definition of DEADBEEF */
#define DEADBEEF ((void *)0xDEADBEEF)

/* definition of the size of a "word" */
#define WORD_SIZE (sizeof(size_t))

/* align up a given number to word size division */
#define ALIGN_UP(num) (((num) + (WORD_SIZE - 1)) & ~(WORD_SIZE - 1))

/* align down a given number to word size division */
#define ALIGN_DOWN(num) ((num) & ~(WORD_SIZE - 1))

/* Macro for keeping the lowest number of two */

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

/* Macro for keeping the highest number of two */

#define MAX(a, b) (((a) < (b)) ? (b) : (a))

/* Macro for compering x and y return values underneath */
#define COMPAREBOOLEAN(x, y) ((x) >= (y))
/* 1 if x >= y, 0 if y > x */


#endif /* __UTILITIES_H__ */
