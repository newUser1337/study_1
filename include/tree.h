#ifndef __TREE__
#define __TREE__

typedef struct TNode
{
    struct TNode *parent;
    struct TNode *left;
    struct TNode *right;
    void *data;
} TNode;

typedef struct Tree
{
    TNode *first;
    void (*printdata)(void *);
    int (*comparedata)(void *, void *);
} Tree;

Tree *tree_init(void (*)(void *), int (*)(void *, void *));
TNode *tree_add(Tree *, void *);
void tree_destr(Tree **);

void tree_print_preorder(Tree *);
void tree_print_postorder(Tree *);
void tree_print_inorder(Tree *);

TNode *tree_find_lowest_common_anc(Tree *, TNode *, TNode *);
TNode *tree_find(Tree *, void *);
void tree_remove(Tree *, TNode *);


#endif