#include <stdio.h>
#include <stdlib.h>
#include "fenw.h"

void _fenw_fill_array(fenw *, int *);
int _fenw_get_sum_elem(int *, size_t, size_t);

fenw *fenw_init(int *array, size_t size)
{
    fenw *fw = (fenw *)malloc(sizeof(fenw));
    fw->array = (int *)malloc(sizeof(int) * size);
    fw->size = size;

    _fenw_fill_array(fw, array);

    return fw;
}

void fenw_destr(fenw **fw)
{
    free((*fw)->array);
    free((*fw));
    *fw = NULL;
}

void _fenw_fill_array(fenw *fw, int *array)
{
    for (size_t i = 0; i < fw->size; i++)
        fw->array[i] = _fenw_get_sum_elem(array, i, i & (i + 1));
}

int _fenw_get_sum_elem(int *array, size_t a, size_t b)
{
    int sum = 0;

    for (size_t i = b; i <= a; i++)
        sum += array[i];

    return sum;
}

void fenw_print(fenw *fw)
{
    printf("Printing fenwick array \n");
    for (size_t i = 0; i < fw->size; i++)
        printf("%d ", fw->array[i]);
    printf("\n");
}

void fenw_add(fenw *fw, size_t ind, int value)
{
    if (ind > fw->size - 1)
        return;
    fw->array[ind] += value;
    fenw_add(fw, ind | (ind + 1), value);
}

int fenw_get_sum(fenw *fw, int l_ind, int r_ind)
{
    int res = 0;
    while (r_ind >= 0)
    {
        res += fw->array[r_ind];
        r_ind = (r_ind & (r_ind + 1)) - 1;
    };
    l_ind--;
    while (l_ind >= 0)
    {
        res -= fw->array[l_ind];
        l_ind = (l_ind & (l_ind + 1)) - 1;
    };

    return res;
}