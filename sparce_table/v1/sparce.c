#include <stdio.h>
#include <stdlib.h>
#include "sparce.h"

void _fill_ST(int **, int *, int, int);
int _set_elemet(int **, int *, int, int);
int _min(int, int);
int _get_log(int);

sparce *sparce_init(int *array, int size)
{
    sparce *sp = (sparce *)malloc(sizeof(sparce));

    sp->size = size;
    sp->log = _get_log(size);
    sp->ST = (int **)malloc(sizeof(int *) * sp->log);
    for (int i = 0; i < sp->log; i++)
        sp->ST[i] = (int *)malloc(sizeof(int) * sp->size);
    _fill_ST(sp->ST, array, sp->size, sp->log);

    return sp;
}

void _fill_ST(int **ST, int *array, int x, int y)
{
    for (int j = 0, z = 1; j < y; z = (1 << ++j))
        for (int i = 0; i + z <= x; i++)
            ST[j][i] = _set_elemet(ST, array, i, j);
}

int _set_elemet(int **ST, int *array, int ix, int log)
{
    if (log == 0)
        return array[ix];

    return _min(ST[log - 1][ix], ST[log - 1][ix + (1 << (log - 1))]);
}

int _min(int a, int b)
{
    return a < b ? a : b;
}

int _get_log(int in)
{
    int i = 0;
    while (in != 1)
    {
        in = in >> 1;
        i++;
    }

    return i + 1;
}

void sparce_print(sparce *sp)
{
    for (int j = 0; j < sp->log; j++)
    {
        for (int i = 0; i < sp->size; i++)
            printf("%d ", sp->ST[j][i]);
        printf("\n");
    }
}

int sparce_rmq(sparce *sp, int r, int l)
{
    if (r > l && sp->size > r && l >= 0)
    {
        int t = _get_log(r - l) - 1;
        if (t)
            return _min(sp->ST[t][l], sp->ST[t][r - (1 << t) + 1]);
        else
            return _min(sp->ST[t][l], sp->ST[t][l]);
    }
    return 0;
}