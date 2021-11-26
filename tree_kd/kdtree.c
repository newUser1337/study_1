#include <stdio.h>
#include <stdlib.h>
#include "kdtree.h"

KDNode *_kdtree_add_root(KDTree *, void *);
KDNode *_kdtree_node_create(void *);
void _kdtree_node_destr_rec(KDNode *);
void _kdtree_node_destr(KDNode **);
KDNode *_kdtree_add_data(KDTree *, KDNode *, void *, int);
KDNode *_kdtree_get_closest(KDTree *, KDNode *, KDNode *, void *);
KDNode *_kdtree_find_nearest(KDTree *, KDNode *, void *, int);
void _kdtree_find_range(KDTree *, KDNode *, int, void *, void *, List *);

void _kdtree_print_inorder(KDNode *, KDTree *);
void _kdtree_print_postorder(KDNode *, KDTree *);
void _kdtree_print_preorder(KDNode *, KDTree *);

KDTree *kdtree_init(int dimensions, void (*printdata)(void *), int (*comparedata)(void *, void *, int), int (*distanse)(void *, void *))
{
    KDTree *kdtree = (KDTree *)malloc(sizeof(KDTree));
    kdtree->comparedata = comparedata;
    kdtree->printdata = printdata;
    kdtree->root = NULL;
    kdtree->K = dimensions;
    kdtree->distanse = distanse;

    return kdtree;
}

KDNode *kdtree_add(KDTree *kdtree, void *data)
{
    KDNode *r_node;
    if (kdtree->root == NULL)
        r_node = _kdtree_add_root(kdtree, data);
    else
        r_node = _kdtree_add_data(kdtree, kdtree->root, data, 0);

    return r_node;
}

KDNode *_kdtree_add_root(KDTree *kdtree, void *data)
{
    KDNode *kdnode = _kdtree_node_create(data);
    kdtree->root = kdnode;

    return kdnode;
}

KDNode *_kdtree_node_create(void *data)
{
    KDNode *kdnode = (KDNode *)malloc(sizeof(KDNode));
    kdnode->data = data;
    kdnode->left = NULL;
    kdnode->right = NULL;
    kdnode->parent = NULL;

    return kdnode;
}

void kdtree_destr(KDTree **kdtree)
{
    if ((*kdtree)->root != NULL)
        _kdtree_node_destr_rec((*kdtree)->root);

    free(*kdtree);
    *kdtree = NULL;
}

void _kdtree_node_destr_rec(KDNode *kdnode)
{
    if (kdnode->left != NULL)
        _kdtree_node_destr_rec(kdnode->left);
    if (kdnode->right != NULL)
        _kdtree_node_destr_rec(kdnode->right);

    _kdtree_node_destr(&kdnode);
}

void _kdtree_node_destr(KDNode **kdnode)
{
    free(*kdnode);
    *kdnode = NULL;
}

KDNode *_kdtree_add_data(KDTree *kdtree, KDNode *kdnode, void *data, int depth)
{
    KDNode *tnewnode, **temp_node;
    if (kdtree->comparedata(data, kdnode->data, depth % kdtree->K) >= 0)
        temp_node = &kdnode->right;
    else
        temp_node = &kdnode->left;
    if (*temp_node == NULL)
    {
        *temp_node = _kdtree_node_create(data);
        (*temp_node)->parent = kdnode;
        tnewnode = *temp_node;
    }
    else
        tnewnode = _kdtree_add_data(kdtree, *temp_node, data, depth + 1);

    return tnewnode;
}

void kdtree_print_preorder(KDTree *kdtree)
{
    printf("Preorder Tree:\n");
    _kdtree_print_preorder(kdtree->root, kdtree);
    printf("End of Tree:\n\n");
}

void _kdtree_print_preorder(KDNode *kdnode, KDTree *kdtree)
{
    if (kdnode == NULL)
        return;
    kdtree->printdata(kdnode->data);

    _kdtree_print_preorder(kdnode->left, kdtree);
    _kdtree_print_preorder(kdnode->right, kdtree);
}

void tree_print_postorder(KDTree *kdtree)
{
    printf("Postorder Tree:\n");
    _kdtree_print_postorder(kdtree->root, kdtree);
    printf("End of Tree:\n\n");
}

void _kdtree_print_postorder(KDNode *kdnode, KDTree *kdtree)
{
    if (kdnode == NULL)
        return;
    _kdtree_print_postorder(kdnode->left, kdtree);
    _kdtree_print_postorder(kdnode->right, kdtree);
    kdtree->printdata(kdnode->data);
}

void tree_print_inorder(KDTree *kdtree)
{
    printf("Inorder Tree:\n");
    _kdtree_print_inorder(kdtree->root, kdtree);
    printf("End of Tree:\n\n");
}

void _kdtree_print_inorder(KDNode *kdnode, KDTree *kdtree)
{
    if (kdnode == NULL)
        return;

    _kdtree_print_inorder(kdnode->left, kdtree);
    kdtree->printdata(kdnode->data);
    _kdtree_print_inorder(kdnode->right, kdtree);
}

KDNode *kdtree_find_nearest(KDTree *kdtree, void *data)
{
    return _kdtree_find_nearest(kdtree, kdtree->root, data, 0);
}

KDNode *_kdtree_find_nearest(KDTree *kdtree, KDNode *root, void *data, int depth)
{
    if (root == NULL)
        return NULL;

    KDNode *next, *other, *temp, *best;
    if (kdtree->comparedata(data, root->data, depth % kdtree->K) < 0)
    {
        next = root->left;
        other = root->right;
    }
    else
    {
        next = root->right;
        other = root->left;
    }
    temp = _kdtree_find_nearest(kdtree, next, data, depth + 1);
    best = _kdtree_get_closest(kdtree, root, temp, data);

    int radius = kdtree->distanse(data, best->data);
    int dist = kdtree->comparedata(data, root->data, depth % kdtree->K);
    if (radius >= dist * dist)
    {
        temp = _kdtree_find_nearest(kdtree, other, data, depth + 1);
        best = _kdtree_get_closest(kdtree, best, temp, data);
    }

    return best;
}

KDNode *_kdtree_get_closest(KDTree *kdtree, KDNode *n1, KDNode *n2, void *data)
{
    if (n1 == NULL)
        return n2;
    if (n2 == NULL)
        return n1;
    int dist_1 = kdtree->distanse(n1->data, data);
    int dist_2 = kdtree->distanse(n2->data, data);
    if (dist_1 < dist_2)
        return n1;
    else
        return n2;
}

void kdtree_find_range(KDTree *kdtree, void *data_min, void *data_max, List *result)
{
    _kdtree_find_range(kdtree, kdtree->root, 0, data_min, data_max, result);
}

void _kdtree_find_range(KDTree *kdtree, KDNode *root, int depth, void *data_min, void *data_max, List *result)
{
    if (root == NULL)
        return;

    printf("depth %d\n", depth);
    
    if (kdtree->comparedata(root->data, data_min, depth % kdtree->K) < 0)
    {
        printf("right ");
        _kdtree_find_range(kdtree, root->right, depth + 1, data_min, data_max, result);
    }
    else
    {
        if (kdtree->comparedata(root->data, data_max, depth % kdtree->K) <= 0)
        {
            printf("right ");
            _kdtree_find_range(kdtree, root->right, depth + 1, data_min, data_max, result);
            if ((kdtree->comparedata(root->data, data_max, (depth + 1) % kdtree->K) <= 0) &&
                (kdtree->comparedata(root->data, data_min, (depth + 1) % kdtree->K) >= 0))
                list_append(result, root->data);
        }
        printf("left ");
        _kdtree_find_range(kdtree, root->left, depth + 1, data_min, data_max, result);
    }
}