#include <stdio.h>
#include "kdtree.h"

#define N 6

typedef struct Point
{
    int x;
    int y;
} Point;

void point_print(void *);
int point_cmp_coord(void *, void *, int);
int distanse(void *, void *);
void point_init(Point *);

int main()
{
    int dimensions = 2;
    Point set[N];
    point_init(set);

    KDTree *kdtree = kdtree_init(dimensions, point_print, point_cmp_coord, distanse);

    for (int i = 0; i < N; i++)
        kdtree_add(kdtree, &set[i]);
    kdtree_print_preorder(kdtree);

    Point target;
    target.x = 1;
    target.y = 1;

    KDNode *knode = kdtree_find_nearest(kdtree, &target);
    point_print(knode->data);

    return 0;
}

void point_print(void *data)
{
    Point *output = data;
    printf("(x,y) (%d,%d)\n", output->x, output->y);
}

int point_cmp_coord(void *point_1, void *point_2, int dim)
{
    return *((int *)point_1 + dim) - *((int *)point_2 + dim);
}

int distanse(void *data_1, void *data_2)
{
    Point *point_1 = data_1, *point_2 = data_2;
    return (point_1->x - point_2->x) * (point_1->x - point_2->x) + (point_1->y - point_2->y) * (point_1->y - point_2->y);
}

void point_init(Point *set)
{
    set[0].x = 5;
    set[0].y = 4;

    set[1].x = 2;
    set[1].y = 6;

    set[2].x = 13;
    set[2].y = 3;

    set[3].x = 8;
    set[3].y = 7;

    set[4].x = 3;
    set[4].y = 1;

    set[5].x = 10;
    set[5].y = 2;
}
