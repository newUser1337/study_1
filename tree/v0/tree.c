#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

node *_node_create(void *);
void _node_destr(node **);
node *_tree_add_first(tree *, void *);
node *_tree_add_data(void *, node *, int (*)(void *, void *));
void _node_destr_rec(node *);

void tree_remove(tree *, node *);
void _tree_remove(tree *, node *);
void _tree_remove_last(tree *, node *);
void _tree_remove_first(tree *, node *);

node *_tree_find_rec(tree *, node *, void *);

void _node_print_preorder(node *, void (*)(void *));
void _node_print_postorder(node *, void (*)(void *));
void _node_print_inorder(node *, void (*)(void *));

tree *tree_init(void (*printdata)(void *), int (*comparedata)(void *, void *))
{
    tree *tr = (tree *)malloc(sizeof(tree));
    tr->comparedata = comparedata;
    tr->printdata = printdata;
    tr->first = NULL;
    tr->cur_size = 0;

    return tr;
}

node *_node_create(void *data)
{
    printf("Node allocated\n");
    node *tn = (node *)malloc(sizeof(node));
    tn->data = data;
    tn->left = NULL;
    tn->right = NULL;
    tn->parent = NULL;

    return tn;
}

void _node_destr(node **tn)
{
    free(*tn);
    *tn = NULL;
    printf("Node deleted \n");
}

node *tree_add(tree *tr, void *data)
{
    tr->cur_size++;
    if (tr->first == NULL)
        return _tree_add_first(tr, data);

    return _tree_add_data(data, tr->first, tr->comparedata);
}

node *_tree_add_first(tree *tr, void *data)
{
    node *tn = _node_create(data);
    tr->first = tn;

    return tn;
}

node *_tree_add_data(void *data, node *tn, int (*comparedata)(void *, void *))
{
    node *tnewnode;
    if (comparedata(data, tn->data) >= 0)
        if (tn->right == NULL)
        {
            tnewnode = _node_create(data);
            tn->right = tnewnode;
            tnewnode->parent = tn;
            return tnewnode;
        }
        else
            return _tree_add_data(data, tn->right, comparedata);
    else
    {
        if (tn->left == NULL)
        {
            tnewnode = _node_create(data);
            tn->left = tnewnode;
            tnewnode->parent = tn;
            return tnewnode;
        }
        else
            return _tree_add_data(data, tn->left, comparedata);
    }
}

void tree_destr(tree **tree)
{
    if ((*tree)->first != NULL)
        _node_destr_rec((*tree)->first);

    free(*tree);
    *tree = NULL;
}

void _node_destr_rec(node *tn)
{
    if (tn->left != NULL)
        _node_destr_rec(tn->left);
    if (tn->right != NULL)
        _node_destr_rec(tn->right);

    _node_destr(&tn);
}

void tree_print_preorder(tree *tr)
{
    printf("Preorder Tree:\n");
    if (tr->first != NULL)
        _node_print_preorder(tr->first, tr->printdata);
    printf("End of Tree:\n\n");
}

void _node_print_preorder(node *tn, void (*printdata)(void *))
{
    if (tn == NULL)
        return;
    printdata(tn->data);

    _node_print_preorder(tn->left, printdata);
    _node_print_preorder(tn->right, printdata);
}

void tree_print_postorder(tree *tr)
{
    printf("Postorder Tree:\n");
    if (tr->first != NULL)
        _node_print_postorder(tr->first, tr->printdata);
    printf("End of Tree:\n\n");
}

void _node_print_postorder(node *tn, void (*printdata)(void *))
{
    if (tn == NULL)
        return;
    _node_print_postorder(tn->left, printdata);
    _node_print_postorder(tn->right, printdata);
    printdata(tn->data);
}

void tree_print_inorder(tree *tr)
{
    printf("Inorder Tree:\n");
    if (tr->first != NULL)
        _node_print_inorder(tr->first, tr->printdata);
    printf("End of Tree:\n\n");
}

void _node_print_inorder(node *tn, void (*printdata)(void *))
{
    if (tn == NULL)
        return;

    _node_print_inorder(tn->left, printdata);
    printdata(tn->data);
    _node_print_inorder(tn->right, printdata);
}

void tree_remove(tree *tr, node *tn)
{
    if (tr->first == tn)
    {
        _tree_remove_first(tr, tn);
    }
    else
    {
        if (tn->left == NULL && tn->right == NULL)
        {
            _tree_remove_last(tr, tn);
        }
        else
        {
            _tree_remove(tr, tn);
        }
    }

    tr->cur_size--;
    _node_destr(&tn);
}

void _tree_remove_first(tree *tr, node *tn)
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

    node *temp, *temp_parent;

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

void _tree_remove_last(tree *tr, node *tn)
{
    if (tn->parent->right == tn)
        tn->parent->right = NULL;
    else
        tn->parent->left = NULL;
}

void _tree_remove(tree *tr, node *tn)
{
    node *p_node = tn->parent;
    node *temp, *temp_parent;

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

node *tree_find(tree *tr, void *data)
{
    return _tree_find_rec(tr, tr->first, data);
}
node *_tree_find_rec(tree *tr, node *trnode, void *data)
{
    if (trnode == NULL)
    {
        printf("Data not found\n");
        return NULL;
    }

    node *res_node;
    int result_cmp = tr->comparedata(data, trnode->data);

    if (result_cmp > 0)
        res_node = trnode->right;
    else if (result_cmp < 0)
        res_node = trnode->left;
    else
        return trnode;

    return _tree_find_rec(tr, res_node, data);
}