#include <stdlib.h>
#include <stdio.h>
#include "disj.h"
#include "tree.h"

void _dsset_print_tree_node_index(void *);
int _dsset_print_tree_node_compare(void *, void *);
DSNode *_dsset_create_node(int, void *);
void _dsset_tree_destr(Tree **);
void _dsset_tree_node_destr_rec(TNode *);
void _dsset_tree_node_destr_rec(TNode *);
void _dsset_free_node_destr(TNode **);

DSSet *dsset_init(void (*printnode)(DSNode *))
{
    DSSet *dsset = (DSSet *)malloc(sizeof(DSSet));
    dsset->treeset = tree_init(_dsset_print_tree_node_index, _dsset_print_tree_node_compare);
    dsset->printnode = printnode;
    return dsset;
}

DSNode *dsset_create_set(DSSet *dsset, int index, void *data)
{
    DSNode *result;
    result = dsset_find_element_by_ind(dsset, index);
    if (result != NULL)
    {
        printf("Element already exists \n");
        return result;
    }
    result = _dsset_create_node(index, data);

    return (tree_add(dsset->treeset, result))->data;
}

DSNode *_dsset_create_node(int index, void *data)
{
    DSNode *node = (DSNode *)malloc(sizeof(DSNode));
    node->data = data;
    node->index = index;
    node->rank = 0;
    node->parent = node;

    return node;
}
DSNode *dsset_find_element_by_ind(DSSet *dsset, int index)
{
    DSNode temp, *result = NULL;
    temp.index = index;
    TNode *tnode_res = tree_find(dsset->treeset, &temp);
    if (tnode_res != NULL)
        result = tnode_res->data;

    return result;
}

void _dsset_print_tree_node_index(void *data)
{
    printf("%d ", ((DSNode *)data)->index);
}

int _dsset_print_tree_node_compare(void *data_1, void *data_2)
{
    DSNode *node_1 = data_1, *node_2 = data_2;

    if (node_1->index > node_2->index)
        return 1;
    else if (node_1->index < node_2->index)
        return -1;
    else
        return 0;
}

DSNode *dsset_find_set(DSSet *dsset, int index)
{
    DSNode *result = dsset_find_element_by_ind(dsset, index);
    if (result == NULL)
    {
        printf("Element not found \n");
        return result;
    }
    while (result != result->parent)
        result = result->parent;

    return result;
}

DSNode *dsset_join_set(DSSet *dsset, int index_1, int index_2)
{
    DSNode *node_1 = dsset_find_set(dsset, index_1);
    DSNode *node_2 = dsset_find_set(dsset, index_2);
    DSNode *temp;
    if (node_1 == NULL || node_2 == NULL)
    {
        printf("Node not found\n");
        return NULL;
    }

    if (node_1 == node_2)
    {
        printf("Sets already connected\n");
        return node_1;
    }

    if (node_1->rank < node_2->rank)
    {
        temp = node_2;
        node_2 = node_1;
        node_1 = temp;
    }

    node_1->parent = node_2;
    node_2->rank++;

    return node_2;
}

void dsset_print_node(DSSet *dsset, int index)
{
    DSNode *node = dsset_find_element_by_ind(dsset, index);
    if (node == NULL)
        printf("Element not found \n");

    dsset->printnode(node);
}

void dsset_destr(DSSet **dsset)
{
    _dsset_tree_destr(&(*dsset)->treeset);
    free(*dsset);
    *dsset = NULL;
}

void _dsset_tree_destr(Tree **tr)
{
    if ((*tr)->first != NULL)
        _dsset_tree_node_destr_rec((*tr)->first);

    free(*tr);
    *tr = NULL;
}

void _dsset_tree_node_destr_rec(TNode *node)
{
    if (node->left != NULL)
        _dsset_tree_node_destr_rec(node->left);
    if (node->right != NULL)
        _dsset_tree_node_destr_rec(node->right);

    _dsset_free_node_destr(&node);
}

void _dsset_free_node_destr(TNode **node)
{
    free((*node)->data);
    free(*node);
    *node = NULL;
}