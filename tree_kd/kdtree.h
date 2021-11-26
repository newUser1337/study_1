#include "list.h"
#ifndef __KDTREE__
#define __KDTREE__

typedef struct KDNode
{
    struct KDNode *parent;
    struct KDNode *left;
    struct KDNode *right;
    void *data;
} KDNode;

typedef struct KDTree
{
    KDNode *root;
    int K; //dimensions
    void (*printdata)(void *);
    int (*comparedata)(void *, void *, int);
    int (*distanse)(void *, void *);
} KDTree;

KDTree *kdtree_init(int, void (*)(void *), int (*)(void *, void *, int), int (*)(void *, void *));
KDNode *kdtree_add(KDTree *, void *);
void kdtree_destr(KDTree **);

void kdtree_print_preorder(KDTree *);
void kdtree_print_postorder(KDTree *);
void kdtree_print_inorder(KDTree *);

KDNode *kdtree_find_nearest(KDTree *, void *);
void kdtree_find_range(KDTree *, void *, void *, List *);

#endif