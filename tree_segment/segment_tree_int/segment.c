#include <stdio.h>
#include <stdlib.h>
#include "segment.h"

int _segtree_fill_array(tree_array *, size_t, int *, size_t, size_t);
int _segtree_search_total(segtree *, tree_array *, tree_range, size_t);
int *_segtree_search_max(segtree *, tree_array *, tree_range, size_t);
int *_segtree_search_min(segtree *, tree_array *, tree_range, size_t);

segtree *segtree_init(int *array, size_t size)
{
    segtree *sg = (segtree *)malloc(sizeof(segtree));
    sg->tree_size = (size - 1) * 2 + 1;
    sg->arr_size = size;
    sg->array = (tree_array *)calloc(sg->tree_size, sizeof(tree_array));
    _segtree_fill_array(sg->array, 0, array, 0, size - 1);

    return sg;
}
int _segtree_fill_array(tree_array *t_arr, size_t t_id, int *array, size_t s_id, size_t e_id)
{
    if (s_id == e_id)
    {
        t_arr[t_id].value = array[s_id];
        t_arr[t_id].range.low = s_id;
        t_arr[t_id].range.high = s_id;
        return t_arr[t_id].value;
    }
    size_t m_id = (s_id + e_id) / 2;
    int val_l = _segtree_fill_array(t_arr, t_id * 2 + 1, array, s_id, m_id);
    int val_r = _segtree_fill_array(t_arr, t_id * 2 + 2, array, m_id + 1, e_id);

    t_arr[t_id].value = val_l + val_r;
    t_arr[t_id].range.low = s_id;
    t_arr[t_id].range.high = e_id;
    return t_arr[t_id].value;
}

void segtree_print(segtree *sg)
{
    for (size_t i = 0; i < sg->tree_size; i++)
        printf("%d ", sg->array[i].value);
    printf("\n");
}

int segtree_quersearch_total(segtree *sg, tree_range range)
{
    int result;
    if (range.low > range.high || range.low < 0 || range.high > sg->arr_size - 1)
    {
        printf("incorrect range\n");
        result = 0;
    }
    else
        result = _segtree_search_total(sg, sg->array, range, 0);

    return result;
}

float segtree_quersearch_average(segtree *sg, tree_range range)
{
    float result;
    if (range.low > range.high || range.low < 0 || range.high > sg->arr_size - 1)
    {
        printf("incorrect range\n");
        result = 0;
    }
    else
        result = (float)_segtree_search_total(sg, sg->array, range, 0) / (range.high - range.low + 1);

    return result;
}

int segtree_quersearch_max(segtree *sg, tree_range range)
{
    int result;
    if (range.low > range.high || range.low < 0 || range.high > sg->arr_size - 1)
    {
        printf("incorrect range\n");
        result = 0;
    }
    else
        result = *_segtree_search_max(sg, sg->array, range, 0);

    return result;
}

int segtree_quersearch_min(segtree *sg, tree_range range)
{
    int result;
    if (range.low > range.high || range.low < 0 || range.high > sg->arr_size - 1)
    {
        printf("incorrect range\n");
        result = 0;
    }
    else
        result = *_segtree_search_min(sg, sg->array, range, 0);

    return result;
}

int _segtree_search_total(segtree *sg, tree_array *array, tree_range range, size_t ind)
{
    if (range.low > array[ind].range.high || range.high < array[ind].range.low)
        return 0;
    if (range.low <= array[ind].range.low && range.high >= array[ind].range.high)
        return array[ind].value;

    int result, val_l, val_r;
    val_l = _segtree_search_total(sg, array, range, ind * 2 + 1);
    val_r = _segtree_search_total(sg, array, range, ind * 2 + 2);
    result = val_l + val_r;
    return result;
}

int *_segtree_search_max(segtree *sg, tree_array *array, tree_range range, size_t ind)
{
    if (range.low > array[ind].range.high || range.high < array[ind].range.low)
        return NULL;
    if (array[ind].range.low == array[ind].range.high)
        return &array[ind].value;

    int *result, *val_l, *val_r;
    val_l = _segtree_search_max(sg, array, range, ind * 2 + 1);
    val_r = _segtree_search_max(sg, array, range, ind * 2 + 2);
    if (val_l != NULL && val_r != NULL)
    {
        if (*val_l > *val_r)
            result = val_l;
        else
            result = val_r;
    }
    else if (val_l == NULL)
        result = val_r;
    else
        result = val_l;

    return result;
}

int *_segtree_search_min(segtree *sg, tree_array *array, tree_range range, size_t ind)
{
    if (range.low > array[ind].range.high || range.high < array[ind].range.low)
        return NULL;
    if (array[ind].range.low == array[ind].range.high)
        return &array[ind].value;

    int *result, *val_l, *val_r;
    val_l = _segtree_search_min(sg, array, range, ind * 2 + 1);
    val_r = _segtree_search_min(sg, array, range, ind * 2 + 2);
    if (val_l != NULL && val_r != NULL)
    {
        if (*val_l < *val_r)
            result = val_l;
        else
            result = val_r;
    }
    else if (val_l == NULL)
        result = val_r;
    else
        result = val_l;

    return result;
}