#include <stdio.h>
#include "segment.h"

#define N 7

int create_tree(segtree *, int, int *, int, int);
void sumdata_int(void *, void *, void *);
void printdata_int(void *);
void print_arr(segtree *, int);
void destr_param(void **);
void copydata_int(void *, void *);
int compardata_int(void *, void *);
void divdata_int(void *, void *, void *);

int main()
{
    int array[N] = {-1, 5, 3, -4, 7, 8, 9};
    segtree *tree = segtree_init(array, sizeof(int), N,
                                 sumdata_int,
                                 printdata_int,
                                 copydata_int,
                                 compardata_int,
                                 divdata_int);
    segtree_print(tree);
    tree_range range;
    range.low = 5;
    range.high = 6;
    void *result;
    result = (void *)malloc(sizeof(int));
    if (segtree_quersearch_total(tree, range, &result))
        printf("result: %d \n", *((int *)result));

    void *max;
    max = (void *)malloc(sizeof(int));
    if (segtree_quersearch_max(tree, range, &max))
        printf("max: %d \n", *((int *)max));

    void *min;
    min = (void *)malloc(sizeof(int));
    if (segtree_quersearch_min(tree, range, &min))
        printf("min: %d \n", *((int *)min));

    void *average;
    average = (void *)malloc(sizeof(float));
    if (segtree_quersearch_average(tree, range, &average))
        printf("average: %f \n", *((float *)average));

    
    free(result);
    free(max);
    free(min);
    free(average);
    segtree_destr(&tree);
    return 0;
}

void sumdata_int(void *val1, void *val2, void *result)
{
    *((int *)result) = *((int *)val1) + *((int *)val2);
}

void printdata_int(void *data)
{
    printf("%d ", *((int *)data));
}

void copydata_int(void *src, void *dst)
{
    *((int *)dst) = *((int *)src);
}

int compardata_int(void *a, void *b)
{
    int result;
    if (*((int *)a) > *((int *)b))
        result = 1;
    else if (*((int *)a) < *((int *)b))
        result = -1;
    else
        result = 0;
    return result;
}

void divdata_int(void *val1, void *val2, void *result)
{
    *((float *)result) = (float)*((int *)val1) / *((int *)val2);
}