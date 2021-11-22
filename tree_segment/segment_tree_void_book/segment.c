#include <stdio.h>
#include <stdlib.h>
#include "segment.h"

void *_segtree_fill_array(segtree *, size_t, void *, size_t, size_t);
void *_segtree_search_total(segtree *, tree_range, size_t, void **);
void *_segtree_search_max(segtree *, tree_range, size_t, void **);
int *_segtree_search_min(segtree *, tree_range, size_t, void **);
void *_segtree_sumdata(segtree *, void *, void *);

segtree *segtree_init(void *array, size_t elem_size, size_t size, 
                        void (*sumdata)(void *, void *, void *), 
                        void (*printdata)(void *), 
                        void (*copydata)(void *, void *), 
                        int (*comparedata)(void *, void *),
                        void (*divdata)(void *, void *, void *))
{
    segtree *sg = (segtree *)malloc(sizeof(segtree));
    sg->tree_size = (size - 1) * 2 + 1;
    sg->arr_size = size;
    sg->sumdata = sumdata;
    sg->printdata = printdata;
    sg->copydata = copydata;
    sg->comparedata = comparedata;
    sg->divdata = divdata;
    sg->elem_size = elem_size;
    sg->array = (void *)malloc(sg->tree_size * elem_size);
    // sg->array = (void *)aligned_alloc(4,sg->tree_size * sizeof(elem_size));
    sg->range = (tree_range *)malloc(sg->tree_size * sizeof(tree_range));
    _segtree_fill_array(sg, 0, array, 0, size - 1);

    return sg;
}

void *_segtree_fill_array(segtree *sg, size_t t_id, void *array, size_t s_id, size_t e_id)
{
    if (s_id == e_id)
    {
        sg->copydata(array + s_id * sg->elem_size, sg->array + t_id * sg->elem_size);
        sg->range[t_id].low = s_id;
        sg->range[t_id].high = s_id;
        return sg->array + t_id * sg->elem_size;
    }
    size_t m_id = (s_id + e_id) / 2;
    void *val_l = _segtree_fill_array(sg, t_id * 2 + 1, array, s_id, m_id);
    void *val_r = _segtree_fill_array(sg, t_id * 2 + 2, array, m_id + 1, e_id);

    sg->sumdata(val_l, val_r, sg->array + t_id * sg->elem_size);
    sg->range[t_id].low = s_id;
    sg->range[t_id].high = e_id;

    return sg->array + t_id * sg->elem_size;
}

void segtree_print(segtree *sg)
{
    for (size_t i = 0; i < sg->tree_size; i++)
        sg->printdata(sg->array + i * sg->elem_size);
    printf("\n");
} 

int segtree_quersearch_total(segtree *sg, tree_range range, void **result)
{
    int resopcode;
    if (range.low > range.high || range.low < 0 || range.high > sg->arr_size - 1)
    {
        printf("incorrect range\n");
        resopcode = 0;
    }
    else
    {
        _segtree_search_total(sg, range, 0, result);
        resopcode = 1;
    }
    return resopcode;
}

void *_segtree_search_total(segtree *sg, tree_range range, size_t ind, void **result)
{
    if (range.low > sg->range[ind].high || range.high < sg->range[ind].low)
        return NULL;
    if (range.low <= sg->range[ind].low && range.high >= sg->range[ind].high)
    {
        if (!ind)
            sg->copydata(sg->array + ind * sg->elem_size, *result);
        return sg->array + ind * sg->elem_size;
    }

    void *val_l, *val_r, *temp_val;
    val_l = _segtree_search_total(sg, range, ind * 2 + 1, result);
    val_r = _segtree_search_total(sg, range, ind * 2 + 2, result);
    if (val_l != NULL && val_r != NULL)
    {
        sg->sumdata(val_l, val_r, *result);
        temp_val = NULL;
    }
    else if (val_l != NULL)
        temp_val = val_l;
    else
        temp_val = val_r;

    return temp_val;
}

int segtree_quersearch_max(segtree *sg, tree_range range, void **result)
{
    int resopcode;
    if (range.low > range.high || range.low < 0 || range.high > sg->arr_size - 1)
    {
        printf("incorrect range\n");
        resopcode = 0;
    }
    else
    {
        _segtree_search_max(sg, range, 0, result);
        resopcode = 1;
    }

    return resopcode;
}

void *_segtree_search_max(segtree *sg, tree_range range, size_t ind, void **result)
{
    if (range.low > sg->range[ind].high || range.high < sg->range[ind].low)
        return NULL;
    if (sg->range[ind].low == sg->range[ind].high)
        return sg->array + ind * sg->elem_size;

    void *val_l, *val_r, *temp_res;
    val_l = _segtree_search_max(sg, range, ind * 2 + 1, result);
    val_r = _segtree_search_max(sg, range, ind * 2 + 2, result);
    if (val_l != NULL && val_r != NULL)
    {
        if (sg->comparedata(val_l, val_r) > 0)
            temp_res = val_l;
        else
            temp_res = val_r;
    }
    else if (val_l == NULL)
        temp_res = val_r;
    else
        temp_res = val_l;

    if (!ind)
        sg->copydata(temp_res, *result);

    return temp_res;
}

int segtree_quersearch_min(segtree *sg, tree_range range, void **result)
{
    int resopcode;
    if (range.low > range.high || range.low < 0 || range.high > sg->arr_size - 1)
    {
        printf("incorrect range\n");
        resopcode = 0;
    }
    else
    {
        _segtree_search_min(sg, range, 0, result);
        resopcode = 1;
    }

    return resopcode;
}

int *_segtree_search_min(segtree *sg, tree_range range, size_t ind, void **result)
{
    if (range.low > sg->range[ind].high || range.high < sg->range[ind].low)
        return NULL;
    if (sg->range[ind].low == sg->range[ind].high)
        return sg->array + ind * sg->elem_size;

    void *val_l, *val_r, *temp_res;
    val_l = _segtree_search_min(sg, range, ind * 2 + 1, result);
    val_r = _segtree_search_min(sg, range, ind * 2 + 2, result);
    if (val_l != NULL && val_r != NULL)
    {
        if (sg->comparedata(val_l, val_r) < 0)
            temp_res = val_l;
        else
            temp_res = val_r;
    }
    else if (val_l == NULL)
        temp_res = val_r;
    else
        temp_res = val_l;

    if (!ind)
        sg->copydata(temp_res, *result);

    return temp_res;
}

void segtree_destr(segtree **sg)
{
    free((*sg)->array);
    free((*sg)->range);
    free(*sg);
    *sg = NULL;
}

int segtree_quersearch_average(segtree *sg, tree_range range, void **result)
{
    int resopcode;
    if (range.low > range.high || range.low < 0 || range.high > sg->arr_size - 1)
    {
        printf("incorrect range\n");
        resopcode = 0;
    }
    else
    {
        int divider = (range.high - range.low + 1);
        void *temp_res = (void*)malloc(sizeof(sg->elem_size));
        _segtree_search_total(sg, range, 0, &temp_res);
        sg->divdata(temp_res, &divider, *result);
        free(temp_res);
        resopcode = 1;
    }
    return resopcode;
}