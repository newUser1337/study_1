#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

typedef struct book
{
    char isbn[10];
    char name[20];
    int pages;
    float cost;
} book;

void book_print_array(void *);
int book_compare(void *, void *);
void book_add_data_to_tree(tree *, int, book *);

int main()
{
    FILE *f = fopen("book", "r");
    int size;
    fscanf(f, "%d", &size);
    printf("File size:: %d \n", size);

    book *Book = (book *)malloc(sizeof(book) * size);
    for (int i = 0; i < size; i++)
        fscanf(f, "%s %s %d %f", (Book + i)->isbn, (Book + i)->name, &(Book + i)->pages, &(Book + i)->cost);

    tree *Tree = tree_init(book_print_array, book_compare);
    book_add_data_to_tree(Tree, size, Book);
    tree_print_preorder(Tree);
    tree_print_inorder(Tree);
    tree_print_postorder(Tree);

    fclose(f);
    free(Book);
    tree_destr(&Tree);
    return 0;
}

void book_add_data_to_tree(tree *Tree, int size, book *array)
{
    for (int i = 0; i < size; i++)
        tree_add(Tree, array + i);
}

void book_print_array(void *value)
{
    printf("%s %s %d %f \n", ((book *)value)->isbn, ((book *)value)->name, ((book *)value)->pages, ((book *)value)->cost);
}
int book_compare(void *v1, void *v2)
{
    float m = ((book *)v1)->pages * ((book *)v1)->cost - ((book *)v2)->pages * ((book *)v2)->cost;
    if(m > 0.2)
        return 1;
    else if(-0.2 <= m && m <= 0.2)
        return 0;
    else 
        return -1;

    return - *((int *)v2);
}