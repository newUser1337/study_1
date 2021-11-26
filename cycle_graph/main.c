#include <stdio.h>
#include "graph_edge.h"

#define N 8

void init_edges(Edge *);
void set_edge(Edge *, int , int , int );

int main()
{
    Edge edge[N];
    init_edges(edge);
    Graph *graph = graphedg_init();
    for (int i = 0; i < N; i++)
        graphedg_add_edges(graph, edge + i);

    if (graphedg_check_for_cycles(graph))
        printf("Cycle\n");

    

    return 0;
}

void init_edges(Edge *edge)
{
    int i = 1;
    set_edge(edge++, i++,7,1);
    set_edge(edge++, i++,1,2);
    set_edge(edge++, i++,2,3);
    set_edge(edge++, i++,3,6);
    set_edge(edge++, i++,6,5);
    set_edge(edge++, i++,4,5);
    set_edge(edge++, i++,4,2);
}

void set_edge(Edge *edge, int index, int from, int to)
{
    edge->index = index;
    edge->from = from;
    edge->to = to;
}