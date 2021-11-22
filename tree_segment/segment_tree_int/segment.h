#include <stdlib.h>

#ifndef __SEGMENT__
#define __SEGMENT__

typedef struct tree_range
{
    size_t low;
    size_t high;
} tree_range;

typedef struct tree_array
{
    int value;
    tree_range range;
} tree_array;

typedef struct segtree
{
    tree_array *array;
    size_t tree_size;
    size_t arr_size;
} segtree;

segtree *segtree_init(int *, size_t);
void segtree_print(segtree *);
int segtree_quersearch_total(segtree *, tree_range);
float segtree_quersearch_average(segtree *, tree_range);
int segtree_quersearch_max(segtree *, tree_range);
int segtree_quersearch_min(segtree *, tree_range);

#endif