/*****************************************************************************
Title: hash table
Author: Omer Avioz
Reviewer: 

Infinity Labs OL95
*****************************************************************************/
#include <assert.h> /* assert */
#include <stdlib.h> /*calloc malloc free */
#include <stdio.h> /*printf*/
#include <sys/types.h>  /*ssize_t*/
#include <math.h>
#include "hash_table.h"
#include "doubly_linked_list.h"
#include "utilities.h"


struct hash_table
{
    dlist_t **arr;
    hash_function_t hash_func;
    is_match_t match_func;
    size_t table_size;
};

int PrintListString(void * data, void *param)
{
    (void)param;
    printf("%s\n", (char *)data);
    return 0;
}

static int CountSize(void *node, void *param)
{
    assert(NULL != node);
    
    *(int *)param += 1;
    return 0;
}

static size_t GetKey(const hash_table_t *hash_table, const void *data)
{
    return ((hash_table->hash_func(data)) % (hash_table->table_size));
}

static void DestroyHashTableBySize(hash_table_t *hash_table, size_t size)
{
    size_t idx = 0;
    for(; idx < size; ++idx)
    {
        DListDestroy(hash_table->arr[idx]);
    }
    free(hash_table->arr);
    free(hash_table);
    hash_table = NULL;

}

static hash_table_t *InitHashTable(hash_table_t *hash_table, size_t table_size)
{
    size_t idx = 0;
    for(idx = 0; idx < table_size ; ++idx)
    {
        hash_table->arr[idx] = DListCreate();

        if (NULL == hash_table->arr[idx])
        {
            DestroyHashTableBySize(hash_table, idx);
            return NULL;
        }
    }

    return hash_table;
}

/*----------------------------------------------------------------------------*/

hash_table_t *HashTableCreate(size_t table_size, hash_function_t hash_func, is_match_hash_t match_func)
{
    hash_table_t *hash_table = NULL;

    assert(NULL != hash_func);
    assert(NULL != match_func);

    hash_table = (hash_table_t *)malloc(sizeof(hash_table_t));
    MALLOC_CHECK(hash_table, HashTableCreate);

    hash_table->arr = malloc(sizeof(dlist_t *) * table_size);
    MALLOC_CHECK_FREE(hash_table->arr, HashTableCreate, hash_table);

    hash_table->hash_func = hash_func;
    hash_table->match_func = match_func;
    hash_table->table_size = table_size;

    return InitHashTable(hash_table, table_size);
}

/*----------------------------------------------------------------------------*/

void HashTableDestroy(hash_table_t *hash_table)
{
    assert(NULL != hash_table);

    DestroyHashTableBySize(hash_table, hash_table->table_size);
}

/*----------------------------------------------------------------------------*/

int HashTableInsert(hash_table_t *hash_table,  void *data)
{
    size_t data_idx = 0;
    dlist_iter_t res = {NULL};

    assert(NULL != hash_table);
    assert(NULL != data);

    data_idx = GetKey(hash_table, data);
    res = DListPushBack(hash_table->arr[data_idx], data);
    if(DListIsSameIter(res, DListEnd(hash_table->arr[data_idx])))
    {
        return 1;
    }
    return 0;
}

/*----------------------------------------------------------------------------*/

void HashTableRemove(hash_table_t *hash_table, const void *data)
{
    size_t data_idx = 0;
    dlist_iter_t res = {NULL};
    dlist_t *list = {NULL};

    assert(NULL != hash_table);
    assert(NULL != data);

    data_idx = GetKey(hash_table, data);
    list = hash_table->arr[data_idx];   
    res = DListFind(DListBegin(list), DListEnd(list),hash_table->match_func,data);
    if(!(DListIsSameIter(res, DListEnd(list))))
    {
        DListRemove(list,res);
    }

}

/*----------------------------------------------------------------------------*/

void *HashTableFind(const hash_table_t *hash_table, const void *data)
{
    size_t data_idx = 0;
    dlist_iter_t res = {NULL};
    dlist_t *list = {NULL};

    assert(NULL != hash_table);
    assert(NULL != data);

    data_idx = GetKey(hash_table, data);
    list = hash_table->arr[data_idx];   
    /*DListForEach(DListBegin(list), DListEnd(list), PrintListString,NULL);*/
    res = DListFind(DListBegin(list), DListEnd(list),hash_table->match_func, data);
    return DListGetData(res);    
}

/*----------------------------------------------------------------------------*/

size_t HashTableSize(const hash_table_t *hash_table)
{
    size_t size = 0;

    assert(NULL != hash_table);

    HashTableForEach(hash_table,CountSize, &size);

    return size;
}

/*----------------------------------------------------------------------------*/

int HashTableIsEmpty(const hash_table_t *hash_table)
{
    size_t idx = 0;

    assert(NULL != hash_table);

    for(; idx < hash_table->table_size; ++idx)
    {
        if(!(DListIsEmpty(hash_table->arr[idx])))
        {
            return 0;
        }
    }
    return 1;
}

/*----------------------------------------------------------------------------*/

int HashTableForEach(const hash_table_t *hash_table, hash_action_t hash_action, void *param)
{
    size_t idx = 0;
    int res = 0;

    assert(NULL != hash_table);
    assert(NULL != hash_action);

    for(; ((idx < hash_table->table_size) && (0 == res)); ++idx)
    {
        dlist_t *list = hash_table->arr[idx];
        res = DListForEach(DListBegin(list), DListEnd(list),hash_action, param);
    }
    return res;

}

double HashTableLoad(const hash_table_t *hash_table)
{
    assert(NULL != hash_table);

    return ((HashTableSize(hash_table)) / (hash_table->table_size));
}

double HashTableSD(const hash_table_t *hash_table)
{

    double load_factor = 0;
    double res = 0;
    size_t idx = 0;

    assert(NULL != hash_table);

    for(; idx < hash_table->table_size ;++idx)
    {

        dlist_t *list = hash_table->arr[idx];
        res += pow(DListSize(list) - load_factor, 2);
    }

    res = sqrt(res / (hash_table->table_size));

    return res;
}

