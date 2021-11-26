#include <stdio.h>
#include "kdtree.h"
#include "list.h"

#define N 12

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
    target.y = 10;

    KDNode *knode = kdtree_find_nearest(kdtree, &target);
    point_print(knode->data);

    Point p1, p2;
    p1.x = 0;
    p1.y = 0;
    p2.x = 2;
    p2.y = 2;
    List *res = list_init(NULL, point_print);

    kdtree_find_range(kdtree, &p1, &p2, res);
    list_print(res);

    list_destr(&res);
    kdtree_destr(&kdtree);
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
    set[0].x = 3;
    set[0].y = 4;

    set[1].x = 5;
    set[1].y = 8;

    set[2].x = 7;
    set[2].y = 6;

    set[3].x = 5;
    set[3].y = 2;

    set[4].x = 2;
    set[4].y = 7;

    set[5].x = 6;
    set[5].y = 9;

    set[6].x = 4;
    set[6].y = 6;

    set[7].x = 6;
    set[7].y = 3;

    set[8].x = 3;
    set[8].y = 3;

    set[9].x = 1;
    set[9].y = 1;

    set[10].x = 1;
    set[10].y = 9;

    set[11].x = 9;
    set[11].y = 7;
}
