#include <stdio.h>
#include <stdlib.h>
#include "fenw.h"

int _fenw_get_sum_elem(int *, size_t, size_t);
int get_next(int);
int get_parent(int);

fenw *fenw_init(int *array, size_t size)
{
    fenw *fw = (fenw *)malloc(sizeof(fenw));
    fw->array = (int *)malloc(sizeof(int) * size + 1);
    fw->size = size;

    for (int i = 0; i < fw->size; i++)
        fenw_update(fw, i, array[i]);

    return fw;
}

int get_next(int in)
{
    int out;
    out = (in | (in + 1));

    return out;
}

int get_parent(int in)
{
    int out;
    out = (in & (in - 1));
    return out;
}

void fenw_update(fenw *fw, int ind, int value)
{
    while (ind < fw->size)
    {
        fw->array[ind + 1] += value;
        ind = get_next(ind);
    };
}

void fenw_print(fenw *fw)
{
    printf("Printing fenwick array \n");
    for (size_t i = 0; i < fw->size; i++)
        printf("%d ", fw->array[i]);
    printf("\n");
}

int _fenw_get_sum(fenw *fw, int ind)
{
    int out = 0;
    while (ind)
    {
        out += fw->array[ind];
        ind = get_parent(ind);
    };
    return out;
}

int fenw_get_sum_lr(fenw *fw, int li, int ri)
{
    int sum = _fenw_get_sum(fw, ri);
    int sub = _fenw_get_sum(fw, li - 1);
    return sum - sub;
}

int fenw_get_sum_element(fenw *fw, int ind)
{
    return fenw_get_sum_lr(fw, ind, ind);
}

void fenw_destr(fenw **fw)
{
    free((*fw)->array);
    free((*fw));
    *fw = NULL;
}