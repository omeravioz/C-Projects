/*****************************************************************************
Title: AVL Tree
Author: Omer Avioz
Reviewer: Yoav Porag

Infinity Labs OL95
*****************************************************************************/

/*-------------------------------- Libraries --------------------------------*/
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc free */
#include "utilities.h"
#include "avl_tree.h" /* Implement of Comparison avl */


/*-----------------------------  Macros -------------------------------------*/
#define NUM_Of_TRAVERSAL_ORDERS (3)

/*---------------------------- Struct declarations --------------------------*/
typedef int (*traversal_action_func_avl_t)(avl_tree_node_t *avl_tree_node,
										   action_func_avl_t func,
										   void *param, int is_on_data);

typedef enum child_side
{
    LEFT = 0,
    RIGHT = 1,
    NUM_OF_ELEMENTS
} child_side_t;

typedef enum insert_or_remove
{
	INSERT = 0,
	REMOVE = 1
} insert_or_remove_t;

struct avl_tree_node
{
	size_t height;
    avl_tree_node_t *children[NUM_OF_ELEMENTS];
    void *data;
};

struct avl_tree
{
	avl_tree_node_t *root;
	compare_function_t compare;
};

/*------------------------ Aux functions declaration ------------------------*/

static void InitLUT();
static traversal_action_func_avl_t LUT[NUM_Of_TRAVERSAL_ORDERS] = {NULL};
static int is_lut_init = 0;

static avl_tree_node_t *GetChild(avl_tree_node_t *avl_tree_node, 
								 child_side_t side);
static size_t GetHeight(avl_tree_node_t *avl_tree_node);
static child_side_t GetOnlyChild(avl_tree_node_t *avl_tree_node);
static int GetNumOfChilds(avl_tree_node_t *avl_tree_node);
static void UpdateHeight(avl_tree_node_t *avl_tree_node);
static avl_tree_node_t *FindMost(avl_tree_node_t *avl_tree_node,
								 child_side_t side);

static avl_tree_node_t *CreateAvlTreeNode(void *data);
static int DestroyNode(void *node, void *param);

static int CountSize(void *node, void *param);


static int GetBalance(avl_tree_node_t *avl_tree_node);
static avl_tree_node_t *Rotate(avl_tree_node_t *avl_tree_node ,
							   child_side_t side);



static avl_tree_node_t *AvlRemoveNode(compare_function_t compare, 
									  avl_tree_node_t *avl_tree_node_to_delete);

static avl_tree_node_t *AvlInsertOrRemove(compare_function_t compare,
								  avl_tree_node_t *avl_tree_node,
								  avl_tree_node_t *input_data,
								  insert_or_remove_t insert_or_remove);

static avl_tree_node_t *AvlFind(compare_function_t compare,
								  avl_tree_node_t *avl_tree_node,
								  const void *input_data);

static int TraversalInorder(avl_tree_node_t *avl_tree_node,
										   action_func_avl_t func,
										   void *param, int is_on_data);
static int TraversalPreorder(avl_tree_node_t *avl_tree_node,
										   action_func_avl_t func,
										   void *param, int is_on_data);
static int TraversalPostorder(avl_tree_node_t *avl_tree_node,
										   action_func_avl_t func,
										   void *param, int is_on_data);


/*--------------------------- Functions definitions -------------------------*/

static void InitLUT()
{
	LUT[INORDER] = TraversalInorder;
	LUT[PREORDER] = TraversalPreorder;
	LUT[POSTORDER] = TraversalPostorder;
}

static avl_tree_node_t *GetChild(avl_tree_node_t *avl_tree_node, 
								 child_side_t side)
{
    assert(NULL != avl_tree_node);

    return avl_tree_node->children[side];
}

static size_t GetHeight(avl_tree_node_t *avl_tree_node)
{
    if(NULL == avl_tree_node)
	{
		return 0;
	}
	
    return avl_tree_node->height;
}

static child_side_t GetOnlyChild(avl_tree_node_t *avl_tree_node)
{
    if(NULL != GetChild(avl_tree_node, LEFT))
    {
        return LEFT;
    }
    return RIGHT;

}

static int GetNumOfChilds(avl_tree_node_t *avl_tree_node)
{
    int num_of_childs = 0;
    if(GetChild(avl_tree_node, RIGHT))
    {
        ++num_of_childs;
    }

    if(GetChild(avl_tree_node ,LEFT))
    {
        ++num_of_childs;
    }

    return num_of_childs;
    
}

static void UpdateHeight(avl_tree_node_t *avl_tree_node)
{
	if(NULL == GetChild(avl_tree_node,LEFT) &&
	  NULL == GetChild(avl_tree_node,RIGHT))
	{
		avl_tree_node->height = 0;
	}
	else
	{
		avl_tree_node->height = 1 + MAX(GetHeight(GetChild(avl_tree_node,LEFT)), 
									GetHeight(GetChild(avl_tree_node,RIGHT)));
	}	
}

static avl_tree_node_t *CreateAvlTreeNode(void *data)
{
	avl_tree_node_t *avl_tree_node = malloc(sizeof(avl_tree_node_t));
	MALLOC_CHECK_RETURN(avl_tree_node, CreateAvlTreeNode, NULL);

	avl_tree_node->children[LEFT] = NULL;
	avl_tree_node->children[RIGHT] = NULL;
	avl_tree_node->data = data;
	avl_tree_node->height = 0;

	return avl_tree_node;

}

static int CountSize(void *node, void *param)
{
    assert(NULL != node);
    
    *(int *)param += 1;
    return 0;
}

static int DestroyNode(void *node, void *param)
{
	(void)param;

    assert(NULL != node);
    
	free((avl_tree_node_t *)node);
	node = NULL;

    return 0;
}
static avl_tree_node_t *FindMost(avl_tree_node_t *avl_tree_node,
								 child_side_t side)
{
	if(GetChild(avl_tree_node, side) == NULL)
	{
		return avl_tree_node;
	}
	else
	{
		return FindMost(GetChild(avl_tree_node, side), side);
	}
	
}

static int GetBalance(avl_tree_node_t *avl_tree_node)
{
	if(NULL == GetChild(avl_tree_node, LEFT))
	{
		return GetHeight(avl_tree_node) * (-1);
	}
	else if(NULL == GetChild(avl_tree_node, RIGHT))
	{
		return GetHeight(avl_tree_node);
	}
	
	return (int)GetHeight(GetChild(avl_tree_node, LEFT))- 
		   (int)GetHeight(GetChild(avl_tree_node, RIGHT));
}

static avl_tree_node_t *Rotate(avl_tree_node_t *avl_tree_node ,
							   child_side_t side)
{
	avl_tree_node_t *child = GetChild(avl_tree_node, !side);

	avl_tree_node->children[!side] = child->children[side];
	child->children[side] = avl_tree_node;

	UpdateHeight(avl_tree_node);
	UpdateHeight(child);

	return child;
}

static avl_tree_node_t *AvlTreeBalance(compare_function_t compare,
						   avl_tree_node_t *avl_tree_node,
						   avl_tree_node_t *input_data,
						   insert_or_remove_t insert_or_remove)
{
	int balance = GetBalance(avl_tree_node);
	if(balance > 1)
	{
		if(((INSERT == insert_or_remove) &&
		   (compare(GetChild(avl_tree_node, LEFT)->data, input_data->data) < 0)) ||
		   ((REMOVE == insert_or_remove) && 
		   (GetBalance(GetChild(avl_tree_node, LEFT)) >= 0)))
		{
			avl_tree_node->children[LEFT] =
			Rotate(avl_tree_node->children[LEFT], LEFT);
	
		}
		return Rotate(avl_tree_node, RIGHT);	
	}

	else if(balance < (-1))
	{
		if(((INSERT == insert_or_remove) &&
		   (compare(GetChild(avl_tree_node, RIGHT)->data, input_data->data) > 0)) ||
		   ((REMOVE == insert_or_remove) && 
		   (GetBalance(GetChild(avl_tree_node, RIGHT)) > 0)))
		{
			avl_tree_node->children[RIGHT] =
			Rotate(avl_tree_node->children[RIGHT], RIGHT);
		}
		return Rotate(avl_tree_node, LEFT);
	}

	return avl_tree_node;
}

static avl_tree_node_t *AvlRemoveNode(compare_function_t compare, 
									  avl_tree_node_t *avl_tree_node_to_delete)
{
	avl_tree_node_t *temp = NULL;
	int num_of_childs = GetNumOfChilds(avl_tree_node_to_delete);
	
	if(0 == num_of_childs)
	{
		free(avl_tree_node_to_delete);
		avl_tree_node_to_delete = NULL;
		return NULL;
	}

	else if(1 == num_of_childs)
	{
		temp = GetChild(avl_tree_node_to_delete,
						GetOnlyChild(avl_tree_node_to_delete));
		free(avl_tree_node_to_delete);
		avl_tree_node_to_delete = NULL;
		return temp;
	}
	else
	{
		temp = FindMost(GetChild(avl_tree_node_to_delete, RIGHT), LEFT);
		avl_tree_node_to_delete->data = temp->data;
		avl_tree_node_to_delete->children[RIGHT] =
			AvlInsertOrRemove(compare, avl_tree_node_to_delete->children[RIGHT], temp, REMOVE);
		return avl_tree_node_to_delete;			  	
	}
}

static avl_tree_node_t *AvlInsertOrRemove(compare_function_t compare,
								  avl_tree_node_t *avl_tree_node,
								  avl_tree_node_t *input_data,
								  insert_or_remove_t insert_or_remove)
{
	assert(NULL != compare);

	if(NULL == avl_tree_node)
	{
		if(insert_or_remove == INSERT)
		{
			return input_data;
		}
		return avl_tree_node;
	}

	if(compare(avl_tree_node->data, input_data->data) > 0)
	{
		avl_tree_node->children[LEFT] = AvlInsertOrRemove(compare,
								 				  avl_tree_node->children[LEFT],
												  input_data,
												  insert_or_remove);

	}
	else if(compare(avl_tree_node->data, input_data->data) < 0)
	{
		avl_tree_node->children[RIGHT] = AvlInsertOrRemove(compare,
								 				  avl_tree_node->children[RIGHT],
												  input_data,
												  insert_or_remove);
		
	}
	else if(insert_or_remove == REMOVE)
	{
		avl_tree_node = AvlRemoveNode(compare, avl_tree_node);
		if(NULL == avl_tree_node)
		{
			return NULL;
		}
	}
	UpdateHeight(avl_tree_node);
	return AvlTreeBalance(compare, avl_tree_node, input_data, insert_or_remove);	
}
static avl_tree_node_t *AvlFind(compare_function_t compare,
								  avl_tree_node_t *avl_tree_node,
								  const void *input_data)
{
	assert(NULL != compare);

	if(NULL == avl_tree_node || compare(avl_tree_node->data, input_data) == 0)
	{
		return avl_tree_node;
	}

	else if(compare(avl_tree_node->data, input_data) > 0)
	{
		return AvlFind(compare,avl_tree_node->children[LEFT],
						 input_data);
	}
	else
	{
		return AvlFind(compare,avl_tree_node->children[RIGHT],
					input_data);	
	}
	
}

static int TraversalInorder(avl_tree_node_t *avl_tree_node,
										   action_func_avl_t func,
										   void *param, int is_on_data)
{
    int res = 0;

	assert(NULL != func);


	if(NULL == avl_tree_node)
	{
		return 0;
	}

	res = res ||
	TraversalInorder(avl_tree_node->children[LEFT], func, param, is_on_data);
	
	res = res || ((is_on_data) ?
	(func(avl_tree_node->data, param)) : func(avl_tree_node, param));
	MALLOC_CHECK_INT_RETURN(res, TraversalPreorder);

	res = res ||
	TraversalInorder(avl_tree_node->children[RIGHT], func, param, is_on_data);

	return res;
}

static int TraversalPreorder(avl_tree_node_t *avl_tree_node,
										   action_func_avl_t func,
										   void *param, int is_on_data)
{
	int res = 0;

	assert(NULL != func);
	if(NULL == avl_tree_node)
	{
		return 0;
	}

	res = res || ((is_on_data) ?
	(func(avl_tree_node->data, param)) : func(avl_tree_node, param));
	MALLOC_CHECK_INT_RETURN(res, TraversalPreorder);

	res = res ||
	TraversalPreorder(avl_tree_node->children[LEFT], func, param, is_on_data );

	res = res ||
	TraversalPreorder(avl_tree_node->children[RIGHT], func, param, is_on_data);	

	return res;
}

static int TraversalPostorder(avl_tree_node_t *avl_tree_node,
										   action_func_avl_t func,
										   void *param, int is_on_data)
{
	int res = 0;

	assert(NULL != func);

	if(NULL == avl_tree_node)
	{
		return 0;
	}
	
	res = res ||
	TraversalPostorder(avl_tree_node->children[LEFT], func, param, is_on_data);

	res = res ||
	TraversalPostorder(avl_tree_node->children[RIGHT], func, param, is_on_data);

	res = res || ((is_on_data) ?
	(func(avl_tree_node->data, param)) : func(avl_tree_node, param));

	return res;
}

/*****************************************************************************
								API's Functions		
*****************************************************************************/
avl_tree_t *AVLTreeCreate(compare_function_t compare)
{
	avl_tree_t *avl_tree = NULL;

	assert(NULL != compare);
	
	avl_tree = malloc(sizeof(avl_tree_t));
	MALLOC_CHECK_RETURN(avl_tree, AVLTreeCreate, NULL);

	avl_tree->root = NULL;
	avl_tree->compare = compare;

	if(0 == is_lut_init)
	{
		InitLUT();
		is_lut_init = 1;
	}

	return avl_tree;
}

/*****************************************************************************/
void AVLTreeDestroy(avl_tree_t *avl_tree)
{
	assert(NULL != avl_tree);

	TraversalPostorder(avl_tree->root, DestroyNode, NULL, 0);
	free(avl_tree);
}

/*****************************************************************************/
int AVLTreeInsert(avl_tree_t *avl_tree, void *data)
{
	avl_tree_node_t *avl_tree_node_to_insert = NULL;

	assert(NULL != avl_tree);
	assert(NULL != avl_tree->compare);
	assert(NULL != data);

	avl_tree_node_to_insert = CreateAvlTreeNode(data);
	MALLOC_CHECK_RETURN(avl_tree_node_to_insert, AVLTreeInsert, -1);
	avl_tree->root = AvlInsertOrRemove(avl_tree->compare, avl_tree->root,
							   		   avl_tree_node_to_insert,
							   		   INSERT);
	return 0;
}

void AVLTreeRemove(avl_tree_t *avl_tree, void *data)
{
	avl_tree_node_t avl_tree_node_to_remove;

	assert(NULL != avl_tree);
	assert(NULL != avl_tree->compare);
	assert(NULL != data);

	avl_tree_node_to_remove.data = data;
	avl_tree_node_to_remove.children[RIGHT] = NULL;
	avl_tree_node_to_remove.children[LEFT] = NULL;
	avl_tree_node_to_remove.height = 0;

	avl_tree->root =
	AvlInsertOrRemove(avl_tree->compare,
					  avl_tree->root,
					  &avl_tree_node_to_remove,
					  REMOVE);
}

/*****************************************************************************/
void *AVLTreeFind(const avl_tree_t *avl_tree, void *data)
{
	avl_tree_node_t *res = NULL;

	assert(NULL !=avl_tree);
	assert(NULL != data);
	
	res = AvlFind(avl_tree->compare, avl_tree->root, (const void *)data);
	if(NULL == res)
	{
		return res;
	}

	return res->data;
}

/*****************************************************************************/
size_t AVLTreeHeight(const avl_tree_t *avl_tree)
{
	assert(NULL != avl_tree);

	if(AVLTreeIsEmpty(avl_tree))
	{
		return 0;
	}
	return GetHeight(avl_tree->root);
}

/*****************************************************************************/
int AVLTreeForEach(avl_tree_t *avl_tree, action_func_avl_t func, void *param,
				   traversal_order_t order)
{
	assert(NULL != avl_tree);
	assert(NULL != func);

	return LUT[order](avl_tree->root, func, param, 1);

}

/*****************************************************************************/
size_t AVLTreeCount(const avl_tree_t *avl_tree)
{
    int counter = 0;
    
    assert(NULL != avl_tree);

    AVLTreeForEach((avl_tree_t *)avl_tree, CountSize, &counter, INORDER);
    return counter;

}

/*****************************************************************************/
int AVLTreeIsEmpty(const avl_tree_t *avl_tree)
{
	assert(NULL != avl_tree);
	return (avl_tree->root == NULL);
}

/*****************************************************************************/
int AVLMultiFind(const avl_tree_t *avl_tree, 
				 is_match_t is_match,
				 const void *param,
				 slist_t *list)
{

}

/*****************************************************************************/
int AVLMultiRemove(const avl_tree_t *avl_tree, 
				 is_match_t is_match,
				 const void *param,
				 slist_t *list)
{

}
