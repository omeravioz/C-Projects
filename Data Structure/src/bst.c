/*****************************************************************************

Title: Binary Sorted Tree
Author: Omer Avioz
Reviewer: 

Infinity Labs OL95
******************************************************************************/
#include <assert.h> /* assert */
#include <stdlib.h> /*calloc malloc free */

#include "bst.h" /* Implement of Comparison Sorts Algorithms */

#define CHECK_MALLOC_AND_RETURN(ptr) if (NULL == ptr) { return NULL; }
#define EXTRACT_NODE(iter) iter
#define NODE_TO_ITER(node) node

typedef enum side_of_child_t
{
	LEFT = 0,
	RIGHT = 1,
	NUM_OF_ELEMENTS
} side_of_child_t;


struct bst_node 
{
	bst_node_t *parent;
	bst_node_t *bst_children[NUM_OF_ELEMENTS];
	void *data;
};


struct binary_sorted_tree
{
	bst_node_t root_stub;
	compare_function_t compare;
	void *params;
};

/*****************************************************************************/
static bst_node_t *GetRoot(bst_t *bst)
{
    return (bst->root_stub.bst_children[LEFT]);
}

static bst_node_t *GetChild(bst_node_t *node, int side)
{
    assert(NULL != node);
    return node->bst_children[side];
}

static bst_node_t *GetParent(bst_node_t *node)
{
    assert(NULL != node);
    return node->parent;
}

static int IsRightChild(bst_node_t *node)
{
    return BSTIsSameIter(GetChild(GetParent(node), RIGHT), node);
}

static int IsLeftChild(bst_node_t *node)
{
    return BSTIsSameIter(GetChild(GetParent(node), LEFT), node);
}

static side_of_child_t SideOfNode(bst_node_t *node)
{
    if(IsLeftChild(node))
    {
        return LEFT;
    }
        return RIGHT;
 
}

static side_of_child_t GetOnlyChild(bst_node_t *node)
{
    if(NULL != GetChild(node, LEFT))
    {
        return LEFT;
    }
    return RIGHT;

}

static bst_node_t *FindMost(bst_node_t * iter, side_of_child_t side)
{
    assert(NULL != iter);

    while(NULL != GetChild(iter, side))
    {
        iter = GetChild(iter, side);
    }
    return iter;   
}

static bst_node_t *CreateNode(void *data, bst_node_t *parent)
{
    bst_node_t * new_node = malloc(sizeof(bst_node_t));
    CHECK_MALLOC_AND_RETURN(new_node);
    new_node->bst_children[LEFT] = NULL;
    new_node->bst_children[RIGHT] = NULL;
    new_node->parent = parent;
    new_node->data = data;
    return new_node;
}

static void RemoveNodeAndTransferPointers(bst_node_t *node)
{
    bst_node_t * parent = NULL;
    bst_node_t * child = NULL;

    assert(NULL != node);

    parent = GetParent(node);
    child = GetChild(node, GetOnlyChild(node));
    parent->bst_children[SideOfNode(node)] = child;
    if(NULL != child)
    {       
        child->parent = parent;
    }
    free(node);
    node = NULL;
}


static int GetNumOfChilds(bst_node_t *node)
{
    int num_of_childs = 0;
    if(GetChild(node, RIGHT))
    {
        ++num_of_childs;
    }

    if(GetChild(node ,LEFT))
    {
        ++num_of_childs;
    }

    return num_of_childs;
    
}

static int CountSize(void *node, void *param)
{
    assert(NULL != node);
    
    *(int *)param += 1;
    return 0;
}

bst_t *BSTCreate(compare_function_t compare ,void *params)
{
	bst_t *bst = NULL;
	
	assert(NULL != compare);
	
	bst = (bst_t *)malloc(sizeof(bst_t));
	CHECK_MALLOC_AND_RETURN(bst);
	
	bst->root_stub.parent = NULL;
	bst->root_stub.bst_children[LEFT] = NULL;
	bst->root_stub.bst_children[RIGHT] = NULL;
	bst->root_stub.data = NULL;
	
	bst->compare = compare;
	
	bst->params = params;
	
	return bst;

}

/*****************************************************************************/

void BSTDestroy(bst_t *bst)
{
    bst_node_t *iter = NULL;

    assert(NULL != bst);
    assert(NULL != bst);

    iter = GetRoot(bst);
    while(!BSTIsEmpty(bst))
    {
        if(NULL != GetChild(iter, LEFT))
        {
            iter = GetChild(iter, LEFT);
        }
        else if(NULL != GetChild(iter, RIGHT))
        {
            iter = GetChild(iter, RIGHT);
        }
        else
        {
            bst_node_t *curr_node = iter;
            iter = GetParent(iter);
            iter->bst_children[SideOfNode(curr_node)] = NULL;          
            free(curr_node);
            curr_node = NULL;
        }
        
    }

    free(bst);
    bst = NULL;

}

/*****************************************************************************/

bst_iter_t BSTInsert(bst_t *bst, void *data)
{
	bst_node_t *node = NULL;
    bst_node_t *prev = NULL;
    int side = 0;
    assert(NULL != bst);

    node = GetRoot(bst);
    prev = BSTEnd(bst); 

    while(NULL != node)
    {
        prev = node;
        if(bst->compare(node->data, data, bst->params) > 0)
        {
            node = GetChild(node, LEFT);
            side = LEFT;
        }
        else
        {
            node = GetChild(node, RIGHT);
            side = RIGHT;
        }
    }

        node = CreateNode(data, prev);
        if(NULL == node)
        {
            return BSTEnd(bst);
        }
        prev->bst_children[side] = node; 

    return NODE_TO_ITER(node);

}

/*****************************************************************************/

void BSTRemove(bst_iter_t iter)
{
    int num_of_childs;
    bst_node_t *parent = NULL;
    bst_node_t *child = NULL;
    bst_node_t *node = NULL;
    assert(NULL != iter);

    node = EXTRACT_NODE(iter);

    num_of_childs = GetNumOfChilds(node);
    if(0 == num_of_childs)
    {
        parent = GetParent(node);
        parent->bst_children[SideOfNode(node)] = NULL;
        free(node);
        node = NULL;
    }

    else if(1 == num_of_childs)
    {
        RemoveNodeAndTransferPointers(node);
    }
    else
    {
        bst_node_t *min_node = FindMost(GetChild(node, RIGHT),LEFT);
        node->data = BSTGetData(min_node);
        RemoveNodeAndTransferPointers(min_node);
        
    }
        
}

/*****************************************************************************/

bst_iter_t BSTFind(bst_t *bst, void *data)
{
	bst_node_t *node = NULL;

    assert(NULL != bst);

    node = GetRoot(bst);

    while(NULL != node)
    {
        if(0 == bst->compare(BSTGetData(node), data, bst->params))
        {
            return NODE_TO_ITER(node);
        }

        else if(bst->compare(BSTGetData(node), data, bst->params) > 0)
        {
            node = GetChild(node, LEFT);
        }

        else
        {
            node = GetChild(node, RIGHT);
        }
    }
    return BSTEnd(bst);

}

/*****************************************************************************/

int BSTForEach(bst_iter_t from, bst_iter_t to, action_function_t func, void *param)
{
    assert(NULL != from);
    assert(NULL != to);
    assert(NULL != func);

    for(; !BSTIsSameIter(from,to); from = BSTNext(from))
    {
        int res = func(BSTGetData(from), param);
        if(res)
        {
            return res;
        }
    }
    return 0;
}

/*****************************************************************************/

size_t BSTSize(const bst_t *bst)
{
    int counter = 0;
    
    assert(NULL != bst);

    BSTForEach(BSTBegin(bst),BSTEnd(bst),CountSize, &counter);
    return counter;
}

/*****************************************************************************/

bst_iter_t BSTBegin(const bst_t *bst)
{
	bst_iter_t root = NULL;

    assert(NULL != bst);

    return(FindMost(BSTEnd(bst), LEFT));
}

/*****************************************************************************/

bst_iter_t BSTEnd(const bst_t *bst)
{
    return NODE_TO_ITER(&(((bst_t *)bst)->root_stub));
}

/*****************************************************************************/

bst_iter_t BSTNext(bst_iter_t iterator)
{
    bst_node_t * node = NULL;
    assert(NULL != iterator);

    node = EXTRACT_NODE(iterator);

    if(NULL != GetChild(node, RIGHT))
    {
        return NODE_TO_ITER(FindMost(GetChild(node, RIGHT), LEFT));   
    }
    else
    {
        while(IsRightChild(node))
        {
            node = GetParent(node);
        }
        return NODE_TO_ITER(GetParent(node));
    }
  
}

/*****************************************************************************/

bst_iter_t BSTPrev(bst_iter_t iterator)
{
    bst_node_t * node = NULL;

    assert(NULL != iterator);

    node = EXTRACT_NODE(iterator);

    if(NULL != GetChild(node, LEFT))
    {
        return NODE_TO_ITER(FindMost(GetChild(node, LEFT), LEFT));
    }
    else
    {
        while(IsLeftChild(node))
        {
            node = GetParent(node);
        }
        return NODE_TO_ITER(GetParent(node));
    }
}

/*****************************************************************************/

void *BSTGetData(bst_iter_t iterator)
{
    return (EXTRACT_NODE(iterator))->data;
}

/*****************************************************************************/

int BSTIsEmpty(const bst_t *bst)
{
    return (NULL == GetRoot((bst_t *)bst));
}

/*****************************************************************************/

int BSTIsSameIter(bst_iter_t iterator1, bst_iter_t iterator2)
{
    return (EXTRACT_NODE(iterator1) == EXTRACT_NODE(iterator2));
}

/*****************************************************************************/





