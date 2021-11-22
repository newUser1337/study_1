#include <stdio.h>
#include "segment.h"

#define N 7

int create_tree(segtree *, int, int *, int, int);
void print_arr(segtree *, int);

int main()
{
    int array[N] = {-1, 5, 3, -4, 7, 8, 9};
    segtree *tree = segtree_init(array, N);
    segtree_print(tree);
    tree_range range;
    range.low = 0;
    range.high = 2;
    int result = segtree_quersearch_total(tree, range);
    printf("result: %d \n", result);
    float average = segtree_quersearch_average(tree, range);
    printf("average: %f \n", average);
    int max = segtree_quersearch_max(tree, range);
    printf("max: %d \n", max);
    int min = segtree_quersearch_min(tree, range);
    printf("min: %d \n", min);
    return 0;
}