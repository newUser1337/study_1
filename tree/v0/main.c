#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

void val_print_array(void *);
int val_compare(void *, void *);
void val_add_data_to_tree(tree *, int, int *);

int main()
{
    FILE *f = fopen("value", "r");
    int size;
    fscanf(f, "%d", &size);
    printf("File size:: %d \n", size);
    int *array = (int *)malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++)
        fscanf(f, "%d", array + i);

    tree *Tree = tree_init(val_print_array, val_compare);
    val_add_data_to_tree(Tree, size, array);
    // tree_print_preorder(Tree);
    // tree_print_inorder(Tree);
    // tree_print_postorder(Tree);

    node *tn1 = tree_find(Tree, array + 3);
    if (tn1 != NULL)
        tree_remove(Tree, tn1);
    node *tn2 = tree_find(Tree, array + 4);
    if (tn2 != NULL)
        tree_remove(Tree, tn2);

    int q = 100;
    tree_add(Tree, &q);
    node *tn3 = tree_find(Tree, &q);
    tree_remove(Tree, tn3);

    tree_print_preorder(Tree);

    fclose(f);
    free(array);
    tree_destr(&Tree);
    return 0;
}

void val_add_data_to_tree(tree *Tree, int size, int *array)
{
    for (int i = 0; i < size; i++)
        tree_add(Tree, array + i);
}

void val_print_array(void *value)
{
    printf("%d \n", *((int *)value));
}
int val_compare(void *v1, void *v2)
{
    return *((int *)v1) - *((int *)v2);
}