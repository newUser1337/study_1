#ifndef __TREE__
#define __TREE__

typedef struct Node
{
    struct Node *parent;
    struct Node *left;
    struct Node *right;
    void *data;
} Node;

typedef struct Tree
{
    Node *first;
    void (*printdata)(void *);
    int (*comparedata)(void *, void *);
} Tree;

Tree *tree_init(void (*)(void *), int (*)(void *, void *));
Node *tree_add(Tree *, void *);
void tree_destr(Tree **);

void tree_print_preorder(Tree *);
void tree_print_postorder(Tree *);
void tree_print_inorder(Tree *);

Node *tree_find_lowest_common_anc(Tree *, Node *, Node *);
Node *tree_find(Tree *, void *);
void tree_remove(Tree *, Node *);


#endif