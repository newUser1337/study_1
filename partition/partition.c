#include "partition.h"
#include <stdlib.h>

partition_generator init_partition_generator(int size)
{
    partition_generator pg;
    pg.count=0;
    pg.n=size;
    pg.a = (int *)malloc(sizeof(int) * size);
    pg.sp = pg.a;
    pg.ep = pg.a + pg.n - 1;

    for (int i = 0; i < size; i++)
        pg.a[i] = 1;

    return pg;
}

void destruct_partition_generator(partition_generator *pg)
{
    free(pg->a);
    pg = NULL;
}

int partition_next(partition_generator *pg)
{

    if(pg->count == 0)
        return ++pg->count;
    
    if(pg->ep == pg->sp)
        return 0;
    
    int *fp = _find_small(pg);
    _set_arr(pg, fp);
    split_arr(pg, fp + 1);
    
    return ++pg->count;
}

void split_arr(partition_generator *pg, int *fp)
{
    int *cp = fp;
    long total = 0;

    do
    {
        total += *cp;
        *cp = 0;
    } while (cp++ != pg->ep);
    pg->ep = fp + total - 1;

    while (total != 0)
    {
        *(fp + total - 1) = 1;
        total--;
    }
}

int *_find_small(partition_generator *pg)
{
    int *fp = pg->sp, *cp = pg->sp;

    do
    {
        if (*fp > *cp)
            fp = cp;
    } while (++cp != pg->ep);
    return fp;
}

void _set_arr(partition_generator *pg, int *fp)
{
    (*fp)++;
    (*pg->ep)--;
}