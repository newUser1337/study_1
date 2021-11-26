#include "list.h"
#include "tree.h"
#include "disj.h"

#ifndef __GRAPH_EDGE__
#define __GRAPH_EDGE__

typedef struct Edge
{
    int index;
    int from;
    int to;
} Edge;

typedef struct Graph
{
    List *edges;
} Graph;

Graph *graphedg_init();
int graphedg_check_for_cycles(Graph *);
void graphedg_print_edges(Graph *);
void graphedg_add_edges(Graph *, Edge *);

#endif