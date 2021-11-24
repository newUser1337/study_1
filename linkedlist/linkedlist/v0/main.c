#include <stdio.h>
#include "linkedlist.h"

void print_int(void *);
void print_point(void *);

typedef struct point
{
    int x;
    int y;
} point;

int main()
{
    int a[] = {1, 2, 3, 4, 5};
    point p[5] = {{7, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};

    linkedlist *ll = linkedlist_init(print_point);
    linkedlist_add(ll, p);
    linkedlistnode *lld = linkedlist_add(ll, p + 1);

    //linkedlist_remove(ll,ll->firstnode);
    linkedlist_add(ll, p + 2);
    linkedlist_insert(ll, lld, p + 3);
    //linkedlist_remove(ll,ll->lastnode);
    //linkedlist_remove(ll,ll->lastnode);
    linkedlist_add(ll, p + 4);
    //linkedlist_add(ll,a+2);

    linkedlist_print(ll, 100);

    linkedlistnode *founddata = linkedlist_find(ll, p);
    if (founddata != NULL)
        printf("found %d\n", *((int *)founddata->data));
    else
        printf("Not found\n");

    founddata = linkedlist_getcurrentnode(ll);
    print_point(founddata->data);
    printf("\n");

    linkedlist_getnextnode(ll);
    founddata = linkedlist_getcurrentnode(ll);
    print_point(founddata->data);
    printf("\n");

    linkedlist_getnextnode(ll);
    founddata = linkedlist_getcurrentnode(ll);
    print_point(founddata->data);
    printf("\n");

    linkedlist_getnextnode(ll);
    founddata = linkedlist_getcurrentnode(ll);
    print_point(founddata->data);
    printf("\n");

    linkedlist_getnextnode(ll);
    founddata = linkedlist_getcurrentnode(ll);
    print_point(founddata->data);
    printf("\n");

    linkedlist_getnextnode(ll);
    founddata = linkedlist_getcurrentnode(ll);
    if(founddata != NULL){
        print_point(founddata->data);
        printf("\n");
    } else 
        printf("End of the list\n");

    //printf("found %d\n", *((int *)founddata->data));


    linkedlist_free(&ll);
}

void print_int(void *value)
{
    printf("%d ", *(int *)value);
}

void print_point(void *value)
{
    printf("(%d,%d) ", ((point *)value)->x, ((point *)value)->y);
}