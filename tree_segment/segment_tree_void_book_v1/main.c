#include <stdio.h>
#include <string.h>
#include "segment.h"

#define N 7
typedef struct book
{
    char name[20];
    int pages;
    int chapter;
} book;

int create_tree(segtree *, int, int *, int, int);
void sumdata_book(void *, void *, void *);
void printdata_book(void *);
void copydata_book(void *, void *);
int compardata_book(void *, void *);
void divdata_int(void *, void *, void *);

void book_init(book *, int);

void book_init(book *Books, int size)
{
    char num[2], book_name[6];
    num[1] = '\0';
    for (int i = 0; i < N; i++)
    {
        Books[i].pages = 50 * (i + 1);
        Books[i].chapter = 2 * (i + 1);
        num[0] = i + 1 + 48;

        strcpy(book_name, "book \0");
        strcat(book_name, num);
        strcpy(Books[i].name, book_name);
    }

    Books[5].pages = 400;
    Books[6].pages = 400;
}

int main()
{
    book Books[N];
    book_init(Books, N);

    segtree *tree = segtree_init(Books, sizeof(book), N,
                                 sumdata_book,
                                 printdata_book,
                                 copydata_book,
                                 compardata_book,
                                 divdata_int);
    segtree_print(tree);
    tree_range range;
    range.low = 5;
    range.high = 6;

    tree_elem *rest;
    rest = (tree_elem *)malloc(sizeof(tree_elem));
    rest->array = (void *)malloc(sizeof(book));
    rest->max = (void *)malloc(sizeof(book));
    rest->min = (void *)malloc(sizeof(book));
    rest->average = (void *)malloc(2*sizeof(float));

    printf("New func\n");

    if (segtree_query(tree, range, rest))
    {
        printf("result:\n");
        printf("pages: %d \n", ((book *)rest->array)->pages);
        printf("chapter: %d \n", ((book *)rest->array)->chapter);
        printf("max:\n");
        printf("name: %s \n", ((book *)rest->max)->name);
        printf("pages: %d \n", ((book *)rest->max)->pages);
        printf("chapter: %d \n", ((book *)rest->max)->chapter);
        printf("min:\n");
        printf("name: %s \n", ((book *)rest->min)->name);
        printf("pages: %d \n", ((book *)rest->min)->pages);
        printf("chapter: %d \n", ((book *)rest->min)->chapter);
        printf("avegare:\n");
        printf("pages: %f \n", *((float *)rest->average));
        printf("chapter: %f \n", *(((float *)rest->average)+1));
    }

    free(rest->array);
    free(rest->min);
    free(rest->max);
    free(rest->average);
    segtree_destr(&tree);
    return 0;
}

void sumdata_book(void *val1, void *val2, void *result)
{
    ((book *)result)->pages = ((book *)val1)->pages + ((book *)val2)->pages;
    ((book *)result)->chapter = ((book *)val1)->chapter + ((book *)val2)->chapter;
}

void printdata_book(void *data)
{
    printf("pages: %d, chapter:  %d\n", ((book *)data)->pages, ((book *)data)->chapter);
}

void copydata_book(void *src, void *dst)
{
    strncpy(((book *)dst)->name, ((book *)src)->name, 20);
    ((book *)dst)->pages = ((book *)src)->pages;
    ((book *)dst)->chapter = ((book *)src)->chapter;
}

int compardata_book(void *a, void *b)
{
    int result;

    if (((book *)a)->pages > ((book *)b)->pages)
        result = 1;
    else if (((book *)a)->pages < ((book *)b)->pages)
        result = -1;
    else
    {
        if (((book *)a)->chapter > ((book *)b)->chapter)
            result = 1;
        else if (((book *)a)->chapter < ((book *)b)->chapter)
            result = -1;
        else
            result = 0;
    }

    return result;
}

void divdata_int(void *val1, void *val2, void *result)
{
    *((float *)result) = (float)((book *)val1)->pages / *((int *)val2);
    *(((float *)result) + 1) = (float)((book *)val1)->chapter / *((int *)val2);
}