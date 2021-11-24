#ifndef __TREE__
#define __TREE__

typedef struct node
{
    struct node *parent;
    struct node *left;
    struct node *right;
    void *data;
} node;

typedef struct tree
{
    int cur_size;
    node *first;
    void (*printdata)(void *);
    int (*comparedata)(void *, void *);
} tree;

tree *tree_init(void (*)(void *), int (*)(void *, void *));
node *tree_add(tree *, void *);
void tree_remove(tree *, node *);
node *tree_find(tree *, void *);

void tree_destr(tree **);
void tree_print_preorder(tree *);
void tree_print_postorder(tree *);
void tree_print_inorder(tree *);
#endif