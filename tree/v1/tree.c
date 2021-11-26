#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

TNode *_tree_add_first(Tree *, void *);
TNode *_tree_add_data(Tree *, TNode *, void *);
TNode *_node_create(void *);
void _node_print_preorder(TNode *, Tree *);
void _node_print_postorder(TNode *, Tree *);
void _node_print_inorder(TNode *, Tree *);
TNode *_tree_find_rec(Tree *, TNode *, void *);
int _tree_get_deep(Tree *, TNode *);

void _node_destr_rec(TNode *);
void _node_destr(TNode **);
void _tree_remove_first(Tree *, TNode *);
void _tree_remove_last(Tree *, TNode *);
void _tree_remove(Tree *, TNode *);

Tree *tree_init(void (*printdata)(void *), int (*comparedata)(void *, void *))
{
    Tree *tr = (Tree *)malloc(sizeof(Tree));
    tr->comparedata = comparedata;
    tr->printdata = printdata;
    tr->first = NULL;

    return tr;
}

TNode *tree_add(Tree *tr, void *data)
{
    TNode *r_node;
    if (tr->first == NULL)
        r_node = _tree_add_first(tr, data);
    else
        r_node = _tree_add_data(tr, tr->first, data);

    return r_node;
}

TNode *_tree_add_first(Tree *tr, void *data)
{
    TNode *tn = _node_create(data);
    tr->first = tn;

    return tn;
}

TNode *_tree_add_data(Tree *tree, TNode *node, void *data)
{
    TNode *tnewnode, **temp_node;
    if (tree->comparedata(data, node->data) >= 0)
        temp_node = &node->right;
    else
        temp_node = &node->left;
    if (*temp_node == NULL)
    {
        *temp_node = _node_create(data);
        (*temp_node)->parent = node;
        tnewnode = *temp_node;
    }
    else
        tnewnode = _tree_add_data(tree, *temp_node, data);

    return tnewnode;
}

TNode *_node_create(void *data)
{
    TNode *node = (TNode *)malloc(sizeof(TNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;

    return node;
}

void tree_destr(Tree **tr)
{
    if ((*tr)->first != NULL)
        _node_destr_rec((*tr)->first);

    free(*tr);
    *tr = NULL;
}

void _node_destr_rec(TNode *node)
{
    if (node->left != NULL)
        _node_destr_rec(node->left);
    if (node->right != NULL)
        _node_destr_rec(node->right);

    _node_destr(&node);
}

void _node_destr(TNode **node)
{
    free(*node);
    *node = NULL;
    printf("TNode deleted \n");
}

void tree_print_preorder(Tree *tree)
{
    printf("Preorder Tree:\n");
    _node_print_preorder(tree->first, tree);
    printf("End of Tree:\n\n");
}

void _node_print_preorder(TNode *node, Tree *tree)
{
    if (node == NULL)
        return;
    tree->printdata(node->data);

    _node_print_preorder(node->left, tree);
    _node_print_preorder(node->right, tree);
}

void tree_print_postorder(Tree *tree)
{
    printf("Postorder Tree:\n");
    _node_print_postorder(tree->first, tree);
    printf("End of Tree:\n\n");
}

void _node_print_postorder(TNode *node, Tree *tree)
{
    if (node == NULL)
        return;
    _node_print_postorder(node->left, tree);
    _node_print_postorder(node->right, tree);
    tree->printdata(node->data);
}

void tree_print_inorder(Tree *tree)
{
    printf("Inorder Tree:\n");
    _node_print_inorder(tree->first, tree);
    printf("End of Tree:\n\n");
}

void _node_print_inorder(TNode *node, Tree *tree)
{
    if (node == NULL)
        return;

    _node_print_inorder(node->left, tree);
    tree->printdata(node->data);
    _node_print_inorder(node->right, tree);
}

TNode *tree_find_lowest_common_anc(Tree *tree, TNode *node_1, TNode *node_2)
{
    int diff = _tree_get_deep(tree, node_1) - _tree_get_deep(tree, node_2);

    if (diff < 0)
        while (diff++)
            node_2 = node_2->parent;
    else if (diff > 0)
        while (diff--)
            node_1 = node_1->parent;

    while (node_1 != NULL && node_1 != node_2)
    {
        node_1 = node_1->parent;
        node_2 = node_2->parent;
    }

    return node_1;
}
int _tree_get_deep(Tree *tree, TNode *node)
{
    int i = 0;
    while (node != NULL)
    {
        i++;
        node = node->parent;
    }
    return i;
}

TNode *tree_find(Tree *tree, void *data)
{
    return _tree_find_rec(tree, tree->first, data);
}
TNode *_tree_find_rec(Tree *tree, TNode *node, void *data)
{
    if (node == NULL)
    {
        printf("Data not found\n");
        return NULL;
    }
    TNode *res_node;
    int result_cmp = tree->comparedata(data, node->data);
    if (result_cmp > 0)
        res_node = _tree_find_rec(tree, node->right, data);
    else if (result_cmp < 0)
        res_node = _tree_find_rec(tree, node->left, data);
    else
        res_node = node;

    return res_node;
}

///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////
void tree_remove(Tree *tree, TNode *node)
{
    if (tree->first == node)
        _tree_remove_first(tree, node);
    else
    {
        if (node->left == NULL && node->right == NULL)
            _tree_remove_last(tree, node);
        else
            _tree_remove(tree, node);
    }

    _node_destr(&node);
}

void _tree_remove_first(Tree *tr, TNode *tn)
{
    if (tn->left == NULL && tn->right == NULL)
    {
        tr->first = NULL;
        return;
    }
    else if (tn->left == NULL)
    {
        tr->first = tn->right;
        if (tn->right != NULL)
            tn->right->parent = NULL;
        return;
    }
    else if (tn->right == NULL)
    {
        tr->first = tn->left;
        if (tn->left != NULL)
            tn->left->parent = NULL;
        return;
    }

    TNode *temp, *temp_parent;

    temp = tn->left;
    while (temp->right != NULL)
        temp = temp->right;
    temp_parent = temp->parent;
    if (temp_parent != tn)
    {
        temp_parent->right = temp->left;
        if (temp->left != NULL)
            temp->left->parent = temp_parent;
    }
    temp->right = tn->right;
    if (temp->right != NULL)
        temp->right->parent = temp;
    if (temp != tn->left)
        temp->left = tn->left;

    temp->parent = NULL;
    tr->first = temp;
}

void _tree_remove_last(Tree *tr, TNode *tn)
{
    if (tn->parent->right == tn)
        tn->parent->right = NULL;
    else
        tn->parent->left = NULL;
}

void _tree_remove(Tree *tr, TNode *tn)
{
    TNode *p_node = tn->parent;
    TNode *temp, *temp_parent;

    if (tn->left == NULL)
    {
        temp = tn->parent;
        if (temp->left == tn)
            temp->left = tn->right;
        else
            temp->right = tn->right;
    }
    else
    {
        temp = tn->left;
        while (temp->right != NULL)
            temp = temp->right;
        temp_parent = temp->parent;
        if (temp_parent != tn)
        {
            temp_parent->right = temp->left;
            if (temp->left != NULL)
                temp->left->parent = temp_parent;
        }
        temp->right = tn->right;
        if (temp->right != NULL)
            temp->right->parent = temp;
        if (temp != tn->left)
            temp->left = tn->left;

        temp->parent = p_node;
        if (p_node->right == tn)
            p_node->right = temp;
        else
            p_node->left = temp;
    }
}