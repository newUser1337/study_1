#include "tree.h"

#ifndef __DISJ__
#define __DISJ__

typedef struct DSNode
{
    struct DSNode *parent;
    int rank;
    int index;
    void *data;
} DSNode;

typedef struct DSSet
{
    Tree *treeset;
    void (*printnode)(DSNode *);
} DSSet;

DSSet *dsset_init(void (*)(DSNode *));
DSNode *dsset_create_set(DSSet *, int, void *);
DSNode *dsset_find_element_by_ind(DSSet *, int);
DSNode *dsset_find_set(DSSet *, int);
DSNode *dsset_join_set(DSSet *, int, int);
void dsset_print_node(DSSet *, int);
void dsset_destr(DSSet **);

#endif