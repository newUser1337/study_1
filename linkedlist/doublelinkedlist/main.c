#include <stdio.h>
#include "doublelinkedlist.h"

void print_int(void *);
void print_point(void *);

typedef struct point
{
    int x;
    int y;
} point;

int main()
{
    //int a[] = {1, 2, 3, 4, 5};
    point p[5] = { {1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};

    doublelinkedlist *dll = doublelinkedlist_init(print_point);
    doublelinkedlist_add(dll, p);
    doublelinkedlistnode *dlld = doublelinkedlist_add(dll, p + 1);

    doublelinkedlist_add(dll, p + 2);
    doublelinkedlist_insert(dll, dlld, p + 3);
    doublelinkedlist_add(dll, p + 4);

    doublelinkedlist_print(dll, 100);

    doublelinkedlistnode *founddata = doublelinkedlist_find(dll, p);
    if (founddata != NULL)
        printf("found %d\n", *((int *)founddata->data));
    else
        printf("Not found\n");

    doublelinkedlist_free(&dll);
}

void print_int(void *value)
{
    printf("%d ", *(int *)value);
}

void print_point(void *value){
    printf("(%d,%d) ", ((point*)value)->x, ((point*)value)->y);
}