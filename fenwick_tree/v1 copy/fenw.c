#include <stdio.h>
#include <stdlib.h>
#include "fenw.h"

int _fenw_get_sum_elem(int *, size_t, size_t);
unsigned int get_next(unsigned int);
unsigned int get_parent(unsigned int);

fenw *fenw_init(int *array, size_t size)
{
    fenw *fw = (fenw *)malloc(sizeof(fenw));
    fw->array = (int *)malloc(sizeof(int) * size);
    fw->size = size;

    for (int i = 0; i < fw->size; i++)
        fenw_update(fw, i, array[i]);

    return fw;
}

unsigned int get_next(unsigned int in)
{
    return in + (in & -in);
}

unsigned int get_parent(unsigned int in)
{
    return in - (in & -in);
}

void fenw_update(fenw *fw, int ind, int value)
{
    while (ind < fw->size)
    {
        fw->array[ind] += value;
        ind = get_next(ind + 1) - 1;
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
    if (ind >= 0)
    {
        while (ind > 0)
        {
            out += fw->array[ind];
            ind = get_parent(ind + 1) - 1;
        };
        out += fw->array[ind];
    }
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