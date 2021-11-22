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
    void *result;
    result = (void *)malloc(sizeof(book));
    if (segtree_quersearch_total(tree, range, &result))
    {
        printf("result:\n");
        printf("pages: %d \n", ((book *)result)->pages);
        printf("chapter: %d \n", ((book *)result)->chapter);
    }

    void *max;
    max = (void *)malloc(sizeof(book));
    if (segtree_quersearch_max(tree, range, &max))
    {
        printf("max:\n");
        printf("name: %s \n", ((book *)max)->name);
        printf("pages: %d \n", ((book *)max)->pages);
        printf("chapter: %d \n", ((book *)max)->chapter);
    }

    void *min;
    min = (void *)malloc(sizeof(book));
    if (segtree_quersearch_min(tree, range, &min))
    {
        printf("min:\n");
        printf("name: %s \n", ((book *)min)->name);
        printf("pages: %d \n", ((book *)min)->pages);
        printf("chapter: %d \n", ((book *)min)->chapter);
    }

    void *average;
    average = (void *)malloc(2 * sizeof(float));
    if (segtree_quersearch_average(tree, range, &average))
    {
        printf("average:\n");
        printf("pages: %f \n", *((float *)average));
        printf("chapter: %f \n", *(((float *)average) + 1));
    }

    free(result);
    free(max);
    free(min);
    free(average);
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