#include <stdio.h>
#include <stdlib.h>
#include "segment.h"

void *_segtree_fill_array(segtree *, size_t, void *, size_t, size_t);
int _segtree_search_total(segtree *, tree_range, size_t, tree_elem *);
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
    sg->t_elem.array = (void *)malloc(sg->tree_size * elem_size);
    sg->t_elem.min = (void *)malloc(sg->tree_size * elem_size);
    sg->t_elem.max = (void *)malloc(sg->tree_size * elem_size);
    // sg->t_elem.average = (void *)malloc(sg->tree_size * elem_size);
    sg->range = (tree_range *)malloc(sg->tree_size * sizeof(tree_range));
    _segtree_fill_array(sg, 0, array, 0, size - 1);

    return sg;
}

void *_segtree_fill_array(segtree *sg, size_t t_id, void *array, size_t s_id, size_t e_id)
{
    if (s_id == e_id)
    {
        sg->copydata(array + s_id * sg->elem_size, sg->t_elem.array + t_id * sg->elem_size);
        sg->copydata(array + s_id * sg->elem_size, sg->t_elem.min + t_id * sg->elem_size);
        sg->copydata(array + s_id * sg->elem_size, sg->t_elem.max + t_id * sg->elem_size);
        // sg->copydata(array + s_id * sg->elem_size, sg->t_elem.average + t_id * sg->elem_size);
        sg->range[t_id].low = s_id;
        sg->range[t_id].high = s_id;
        return sg->t_elem.array + t_id * sg->elem_size;
    }
    size_t m_id = (s_id + e_id) / 2;
    void *val_l = _segtree_fill_array(sg, t_id * 2 + 1, array, s_id, m_id);
    void *val_r = _segtree_fill_array(sg, t_id * 2 + 2, array, m_id + 1, e_id);

    sg->sumdata(val_l, val_r, sg->t_elem.array + t_id * sg->elem_size);
    sg->range[t_id].low = s_id;
    sg->range[t_id].high = e_id;

    if (sg->comparedata(sg->t_elem.max + (2 * t_id + 1) * sg->elem_size, sg->t_elem.max + (2 * t_id + 2) * sg->elem_size) > 0)
        sg->copydata(sg->t_elem.max + (2 * t_id + 1) * sg->elem_size, sg->t_elem.max + t_id * sg->elem_size);
    else
        sg->copydata(sg->t_elem.max + (2 * t_id + 2) * sg->elem_size, sg->t_elem.max + t_id * sg->elem_size);

    if (sg->comparedata(sg->t_elem.min + (2 * t_id + 1) * sg->elem_size, sg->t_elem.min + (2 * t_id + 2) * sg->elem_size) < 0)
        sg->copydata(sg->t_elem.min + (2 * t_id + 1) * sg->elem_size, sg->t_elem.min + t_id * sg->elem_size);
    else
        sg->copydata(sg->t_elem.min + (2 * t_id + 2) * sg->elem_size, sg->t_elem.min + t_id * sg->elem_size);

    // int divider = (e_id - s_id + 1);
    // sg->divdata(sg->t_elem.array + t_id * sg->elem_size, &divider, sg->t_elem.average + t_id * sg->elem_size);

    return sg->t_elem.array + t_id * sg->elem_size;
}

void segtree_print(segtree *sg)
{
    for (size_t i = 0; i < sg->tree_size; i++)
        sg->printdata(sg->t_elem.array + i * sg->elem_size);
    printf("\n");
}


void segtree_destr(segtree **sg)
{
    free((*sg)->t_elem.array);
    free((*sg)->t_elem.max);
    free((*sg)->t_elem.min);
    // free((*sg)->t_elem.average);
    free((*sg)->range);
    free(*sg);
    *sg = NULL;
}

int segtree_query(segtree *sg, tree_range range, tree_elem *result)
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
        _segtree_search_total(sg, range, 0, result);
        sg->divdata(result->array, &divider, result->average);
        resopcode = 1;
    }
    return resopcode;
}

int _segtree_search_total(segtree *sg, tree_range range, size_t ind, tree_elem *result)
{
    if (range.low > sg->range[ind].high || range.high < sg->range[ind].low)
        return -1;
    if (range.low <= sg->range[ind].low && range.high >= sg->range[ind].high)
    {
        if (!ind)
        {
            sg->copydata(sg->t_elem.array + ind * sg->elem_size, result->array);
            sg->copydata(sg->t_elem.max + ind * sg->elem_size, result->max);
            sg->copydata(sg->t_elem.min + ind * sg->elem_size, result->min);
        }
        return ind;
    }

    int val_l, val_r, temp_val;
    val_l = _segtree_search_total(sg, range, ind * 2 + 1, result);
    val_r = _segtree_search_total(sg, range, ind * 2 + 2, result);
    if (val_l != -1 && val_r != -1)
    {
        sg->sumdata(sg->t_elem.array + val_l * sg->elem_size, sg->t_elem.array + val_r * sg->elem_size, result->array);

        if (sg->comparedata(sg->t_elem.max + val_l * sg->elem_size, sg->t_elem.max + val_r * sg->elem_size) > 0)
            sg->copydata(sg->t_elem.max + val_l * sg->elem_size, result->max);
        else
            sg->copydata(sg->t_elem.max + val_r * sg->elem_size, result->max);

        if (sg->comparedata(sg->t_elem.min + val_l * sg->elem_size, sg->t_elem.min + val_r * sg->elem_size) < 0)
            sg->copydata(sg->t_elem.min + val_l * sg->elem_size, result->min);
        else
            sg->copydata(sg->t_elem.min + val_r * sg->elem_size, result->min);

        temp_val = -1;
    }
    else if (val_l != -1)
        temp_val = val_l;
    else
        temp_val = val_r;

    return temp_val;
}