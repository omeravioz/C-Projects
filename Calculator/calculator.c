#include <assert.h> /*assert*/  
#include <math.h>   /*pow*/
#include <stdlib.h> /*malloc*/

#include "calculator.h"
#include "stack.h"
#include "string.h"


#define CHECK_MALLOC_AND_RETURN(ptr,MALLOC_FAILED) if (NULL == ptr) { return MALLOC_FAILED; }
#define SIZE_OF_ASCII_TABLE 256
#define NUM_OF_STATES 2 

/*---------------------------- Struct declarations --------------------------*/

typedef enum state
{
    WAIT_FOR_NUM = 0,
	WAIT_FOR_OP = 1,
    FINISH = 2

}state_t;

typedef struct response
{
    stack_t *num_stack;
    stack_t *op_stack;
    char *exp;
    state_t *state;
    int *BrackCounter;

}response_t;

typedef calc_status_t (*calc_func_t)(response_t *response);
typedef double (*op_func_t)(double num1, double num2);

static calc_func_t lut_calc[SIZE_OF_ASCII_TABLE][NUM_OF_STATES];
static int LUT_Priority[256] = {0};
static op_func_t LUT_Action_Funcs[256] = {NULL};

/*------------------------ Aux functions definitions ------------------------*/


/******************************************************************************
*	          	Functions for operation on two top nums  	  	  	  *
*   														  			  	  *
******************************************************************************/
static double Multiply_Nums(double first, double second)
{
    return (first * second);
}

static double Division_Nums(double first, double second)
{
    return (first / second);
}

static double Add_Nums(double first, double second)
{
    return (first + second);
}

static double Sub_Nums(double first, double second)
{
    return (first - second);
}

static double Pow_Nums(double first, double second)
{
    return pow(first, second);
   
}


static void CalcTwoNumbers(response_t *response, char last_op)
{
    double num1 = 0.0;
    double num2 = 0.0;
    num1 = *(double *)StackPeek(response->num_stack);
    StackPop(response->num_stack);
    num2 = *(double *)StackPeek(response->num_stack);
    StackPop(response->num_stack);

    num2 = LUT_Action_Funcs[last_op](num2,num1);
    StackPush(response->num_stack, (const double *)&num2);
    StackPop(response->op_stack);

}


static calc_status_t CALC_Add_Num(response_t *response)
{
    double num;
    char *str = NULL;

    assert(NULL != response);

    num = strtod(response->exp, &str);
    StackPush(response->num_stack,(const double *)&num);
    response->exp = str;
    *response->state = WAIT_FOR_OP;
    return SUCCESS;

}

static calc_status_t CALC_Add_Op(response_t *response)
{
    char curr_op = 0;
    char last_op = 0;

    
    assert(NULL != response);
    
    curr_op = *response->exp;

    while(!StackIsEmpty(response->op_stack) &&
           LUT_Priority[curr_op] <= LUT_Priority[(char)*(char *)StackPeek(response->op_stack)])
    {
        CalcTwoNumbers(response, (char)*(char *)StackPeek(response->op_stack));     
    }
    
    StackPush(response->op_stack,(const char *)&curr_op);
    ++(response->exp);
    *response->state = WAIT_FOR_NUM;
    return SUCCESS; 
}



static calc_status_t CalcOpenBrack(response_t *response)
{
    char first_char = 0;

    assert(NULL != response);

    first_char = *response->exp;
	StackPush(response->op_stack, (const char *)&first_char);
    ++(*response->BrackCounter);
	++(response->exp);

	return SUCCESS;
}



static calc_status_t CalcSpace(response_t *response)
{
    assert(NULL != response);
	
    ++(response->exp);
	return SUCCESS;
}

static calc_status_t CalcErrNumAfterNum(response_t *response)
{
    assert(NULL != response);

    *response->state = NUM_AFTER_NUM;
    return FINISH;
}

static calc_status_t CalcErrOpAfterOp(response_t *response)
{
    assert(NULL != response);

    *response->state = FINISH;
    return OP_AFTER_OP;
}

static calc_status_t CalcErrInvalidChar(response_t *response)
{
    assert(NULL != response);

    *response->state = FINISH;
    return INVALID_CHAR;
}

static calc_status_t CalcErrSyntaxError(response_t *response)
{
    assert(NULL != response);

    *response->state = FINISH;
    return SYNTAX_ERROR;
}

static calc_status_t CalcErrBrack(response_t *response)
{
    assert(NULL != response);

    *response->state = FINISH;
    return PARENTHESIS_UNBALANCED;
}

static calc_status_t CalcEndOfExp(response_t *response)
{
    char last_op = 0;

    if(*response->BrackCounter > 1)
    {
        *response->state = FINISH;
        return PARENTHESIS_UNBALANCED;
    }

    while(!StackIsEmpty(response->op_stack))
    {
        last_op = *(char *)StackPeek(response->op_stack);
        CalcTwoNumbers(response, last_op);       
    }
    *response->state = FINISH;
    return SUCCESS;
}

static calc_status_t CalcCloseBrack(response_t *response)
{
    char last_op = 0;

    assert(NULL != response);

    --(*response->BrackCounter);
    if(*response->BrackCounter <= 0)
    {
        *response->state = FINISH;
        return PARENTHESIS_UNBALANCED;
    }

    last_op = *(char *)StackPeek(response->op_stack);

    while(LUT_Priority[last_op] > 0)
    {
        CalcTwoNumbers(response, last_op);
        last_op = *(char *)StackPeek(response->op_stack);     
    }
    StackPop(response->op_stack);
    ++(response->exp);
    
    return SUCCESS;
}

static calc_status_t CalcAddOrSub(response_t *response)
{
    double num;
    char *str = NULL;

    assert(NULL != response);

    num = strtod(response->exp, &str);

    if(str != response->exp)
    {
        return lut_calc['0' + (unsigned int)num % 10][*response->state](response);  
    }
    else
    {
        return CalcErrOpAfterOp(response);
    }
            
   
}

static response_t *CreateResponse(char *exp, state_t *state, int *BrackCounter)
{
    response_t *response = NULL;
    stack_t *num_stack = NULL;
    stack_t *op_stack = NULL;

    assert(NULL != exp);
    assert(NULL != state);

    response = malloc(sizeof(response_t));
    if (NULL == response)
    {
        return NULL;
    }

    num_stack = StackCreate(strlen(exp), sizeof(double));
    if (NULL == num_stack)
    {
        free(response);
        return NULL;
    }

    op_stack = StackCreate(strlen(exp), sizeof(char));
    if (NULL == op_stack)
    {
        free(response);
        StackDestroy(num_stack);
        return NULL;
    }
    response->num_stack = num_stack;
    response->op_stack = op_stack;
    response->exp = exp;
    response->state = state;
    response->BrackCounter = BrackCounter;

   return response;
}

static void Init_Lut_Calc()
{
    int i;
    for(i = 0; i < SIZE_OF_ASCII_TABLE; ++i)
    {
        if(i >= '0' && i <= '9')
        {
            lut_calc[i][WAIT_FOR_NUM] = &CALC_Add_Num;
            lut_calc[i][WAIT_FOR_OP] = &CalcErrNumAfterNum;
        }

        else if(LUT_Priority[i] >= 1 && LUT_Priority[i] <= 3)
        {
            lut_calc[i][WAIT_FOR_NUM] = &CalcErrOpAfterOp;
            lut_calc[i][WAIT_FOR_OP] = &CALC_Add_Op;
        }

        else
        {
            lut_calc[i][WAIT_FOR_NUM] = &CalcErrInvalidChar;
            lut_calc[i][WAIT_FOR_OP] = &CalcErrInvalidChar;
        }
        
    }

    lut_calc[' '][WAIT_FOR_NUM] = &CalcSpace;
    lut_calc[' '][WAIT_FOR_OP] = &CalcSpace;

    lut_calc[')'][WAIT_FOR_NUM] = &CalcErrBrack;
    lut_calc[')'][WAIT_FOR_OP] = &CalcCloseBrack;

    lut_calc['('][WAIT_FOR_NUM] = &CalcOpenBrack;
    lut_calc['('][WAIT_FOR_OP] = &CalcErrSyntaxError;

    lut_calc['-'][WAIT_FOR_NUM] = CalcAddOrSub;
    lut_calc['+'][WAIT_FOR_NUM] = CalcAddOrSub;

    
    lut_calc['\0'][WAIT_FOR_OP] = &CalcEndOfExp;


}

static void Init_Lut_Action_Funcs()
{
    LUT_Action_Funcs['*'] = Multiply_Nums;
    LUT_Action_Funcs['/'] = Division_Nums;
    LUT_Action_Funcs['+'] = Add_Nums;
    LUT_Action_Funcs['-'] = Sub_Nums;
    LUT_Action_Funcs['^'] = Pow_Nums;
}

static void Init_LUT_Priority()
{
    LUT_Priority['('] = 0;
    LUT_Priority['+'] = 1;
    LUT_Priority['-'] = 1;
    LUT_Priority['*'] = 2;
    LUT_Priority['/'] = 2;
    LUT_Priority['^'] = 3; 
   
}
static void CalcDestroy(response_t *response ,char *exp_cpy)
{
    StackDestroy(response->op_stack);
    StackDestroy(response->num_stack);
    free(response);
    free(exp_cpy);
}

calc_status_t Calc(const char *exp, double *res)
{
    state_t state = WAIT_FOR_NUM;
    response_t *response = NULL;
    
    char *str = NULL;
    char *exp_cpy = NULL;
    int BrackCounter = 1;
    calc_status_t curr_status = SUCCESS;
    double inf = 1.0/0.0;
    
    assert(NULL != exp);
    assert(NULL != res);

    exp_cpy = malloc(strlen(exp) + 1);
    CHECK_MALLOC_AND_RETURN(exp_cpy, MALLOC_FAILED);
    strcpy(exp_cpy, (char *)exp);

    response = CreateResponse(exp_cpy, &state, &BrackCounter);
    CHECK_MALLOC_AND_RETURN(response,MALLOC_FAILED);

    Init_Lut_Action_Funcs();
    Init_LUT_Priority();
    Init_Lut_Calc();

    while(*response->state != FINISH)
    {
        curr_status = lut_calc[(char)(*response->exp)][*response->state](response);
    }
    
    if(!StackIsEmpty(response->num_stack))
    {
        *res = *(double *)StackPeek(response->num_stack);
        if(curr_status != SUCCESS)
        {
        *res = 0; 
        }
        else if(*res == inf)
        {
            curr_status = DIVIDE_BY_0;
            *res = 0;
        }
    }

    CalcDestroy(response,exp_cpy);

    return curr_status;
}




