#include <stdlib.h>

#ifndef __FENW__
#define __FENW__

typedef struct fenw
{
    int *array;
    size_t size;
} fenw;

fenw *fenw_init(int *, size_t);
void fenw_destr(fenw **);
void fenw_print(fenw *);

void fenw_add(fenw *, size_t, int);
int fenw_get_sum(fenw *, int, int);
#endif