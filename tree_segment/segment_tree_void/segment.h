#include <stdlib.h>

#ifndef __SEGMENT__
#define __SEGMENT__

typedef struct tree_range
{
    size_t low;
    size_t high;
} tree_range;

typedef struct segtree
{
    size_t tree_size;
    size_t arr_size;
    size_t elem_size;
    void *array;
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

int segtree_quersearch_total(segtree *, tree_range, void **);
int segtree_quersearch_average(segtree *, tree_range, void **);
int segtree_quersearch_max(segtree *, tree_range, void **);
int segtree_quersearch_min(segtree *, tree_range, void **);

#endif