#include "list.h"
#include "tree.h"

#ifndef __GRAPH__
#define __GRAPH__

typedef struct GNode
{
    List *list_nodes;
    int index;
    void *data;
} GNode;

typedef struct Graph
{
    Tree *tree;
    int size;
    void (*printdata)(void *);
    int (*cmpdata)(void *, void *);
} Graph;

Graph *graph_init(void (*)(void *),
                  int (*)(void *, void *));
GNode *graph_add(Graph *, int, void *);
void graph_connect(Graph *, int, int, int *);
void graph_connect_direct(Graph *, int, int, int *);
GNode *graph_find_ind(Graph *, int);
void graph_print(Graph *);
void graph_dfs(Graph *, int);
void graph_dfs_rec(Graph *, int);
void graph_bfs(Graph *, int);
int graph_cycle(Graph *, int);
void graph_destr(Graph **);
void graph_get_component(Graph *, List *);
int graph_direct_cycle(Graph *, List**);

#endif