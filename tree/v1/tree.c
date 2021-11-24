#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

Node *_tree_add_first(Tree *, void *);
Node *_tree_add_data(Tree *, Node *, void *);
Node *_node_create(void *);
void _node_print_preorder(Node *, Tree *);
void _node_print_postorder(Node *, Tree *);
void _node_print_inorder(Node *, Tree *);
Node *_tree_find_rec(Tree *, Node *, void *);

void _node_destr_rec(Node *);
void _node_destr(Node **);
void _tree_remove_first(Tree *, Node *);
void _tree_remove_last(Tree *, Node *);
void _tree_remove(Tree *, Node *);

Tree *tree_init(void (*printdata)(void *), int (*comparedata)(void *, void *))
{
    Tree *tr = (Tree *)malloc(sizeof(Tree));
    tr->comparedata = comparedata;
    tr->printdata = printdata;
    tr->first = NULL;

    return tr;
}

Node *tree_add(Tree *tr, void *data)
{
    Node *r_node;
    if (tr->first == NULL)
        r_node = _tree_add_first(tr, data);
    else
        r_node = _tree_add_data(tr, tr->first, data);

    return r_node;
}

Node *_tree_add_first(Tree *tr, void *data)
{
    Node *tn = _node_create(data);
    tr->first = tn;

    return tn;
}

Node *_tree_add_data(Tree *tree, Node *node, void *data)
{
    Node *tnewnode, **temp_node;
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

Node *_node_create(void *data)
{
    Node *node = (Node *)malloc(sizeof(Node));
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

void _node_destr_rec(Node *node)
{
    if (node->left != NULL)
        _node_destr_rec(node->left);
    if (node->right != NULL)
        _node_destr_rec(node->right);

    _node_destr(&node);
}

void _node_destr(Node **node)
{
    free(*node);
    *node = NULL;
    printf("Node deleted \n");
}

void tree_print_preorder(Tree *tree)
{
    printf("Preorder Tree:\n");
    _node_print_preorder(tree->first, tree);
    printf("End of Tree:\n\n");
}

void _node_print_preorder(Node *node, Tree *tree)
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

void _node_print_postorder(Node *node, Tree *tree)
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

void _node_print_inorder(Node *node, Tree *tree)
{
    if (node == NULL)
        return;

    _node_print_inorder(node->left, tree);
    tree->printdata(node->data);
    _node_print_inorder(node->right, tree);
}

int _tree_get_deep(Tree *, Node *);


Node *tree_find_lowest_common_anc(Tree *tree, Node *node_1, Node *node_2)
{
    int diff = _tree_get_deep(tree, node_1) - _tree_get_deep(tree, node_2);

    if(diff < 0)
    {
        while(diff)
        {
            diff++;
            node_2 = node_2->parent;
        }
    }
    else if(diff > 0)
    {
        while(diff)
        {
            diff--;
            node_1 = node_1->parent;
        }
    }
    
    while (node_1 != NULL)
    {
        if(node_1 == node_2)
            return node_1;
        node_1 = node_1->parent;
        node_2 = node_2->parent;
    }
    return NULL;
    
}
int _tree_get_deep(Tree *tree, Node *node)
{
    int i = 0;
    while (node != NULL)
    {
        i++;
        node = node->parent;
    }
    return i;
}

Node *tree_find(Tree *tree, void *data)
{
    return _tree_find_rec(tree, tree->first, data);
}
Node *_tree_find_rec(Tree *tree, Node *node, void *data)
{
    if (node == NULL)
    {
        printf("Data not found\n");
        return NULL;
    }
    Node *res_node;
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
void tree_remove(Tree *tree, Node *node)
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

void _tree_remove_first(Tree *tr, Node *tn)
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

    Node *temp, *temp_parent;

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

void _tree_remove_last(Tree *tr, Node *tn)
{
    if (tn->parent->right == tn)
        tn->parent->right = NULL;
    else
        tn->parent->left = NULL;
}

void _tree_remove(Tree *tr, Node *tn)
{
    Node *p_node = tn->parent;
    Node *temp, *temp_parent;

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