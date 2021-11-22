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
    for(size_t i = 0; i < fw->size;i++)
        printf("%d ",fw->array[i]);
    printf("\n");
}