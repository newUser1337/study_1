#include <stdlib.h>

#ifndef __SEGMENT__
#define __SEGMENT__

typedef struct tree_range
{
    size_t low;
    size_t high;
} tree_range;

typedef struct tree_elem
{
    void *array;
    void *min;
    void *max;
    void *average;
} tree_elem;

typedef struct segtree
{
    size_t tree_size;
    size_t arr_size;
    size_t elem_size;
    tree_elem t_elem;
    tree_range *range;
    void (*sumdata)(void *, void *, void *);
    void (*printdata)(void *);
    void (*copydata)(void *, void *);
    int (*comparedata)(void *, void *);
    void (*divdata)(void *, void *, void *);
} segtree;

segtree *segtree_init(void *, size_t, size_t,
                      void (*)(void *, void *, void *),
                      void (*)(void *),
                      void (*)(void *, void *),
                      int (*)(void *, void *),
                      void (*)(void *, void *, void *));
void segtree_destr(segtree **);
void segtree_print(segtree *);

int segtree_query(segtree *, tree_range, tree_elem *);

#endif