#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "disj.h"
#include "graph_edge.h"

void print_egdes(void *);
int compare_edges(void *, void *);
void print_set_vertex(DSNode *);

Graph *graphedg_init()
{
    Graph *graphedge = (Graph *)malloc(sizeof(Graph));
    graphedge->edges = list_init(compare_edges, print_egdes);

    return graphedge;
}

int graphedg_check_for_cycles(Graph *graphedge)
{
    DSSet *dsset = dsset_init(print_set_vertex);
    DSNode *ver_from, *ver_to, *ver_from_parent, *ver_to_parent;
    LNode *lnode = graphedge->edges->first;
    int res = 0;
    while (lnode != NULL)
    {
        Edge *edge = lnode->data;
        ver_from_parent = dsset_find_set(dsset, (dsset_create_set(dsset, edge->from, NULL))->index);
        ver_to_parent = dsset_find_set(dsset, (dsset_create_set(dsset, edge->to, NULL))->index);
        if (ver_from_parent->index == ver_to_parent->index)
        {
            res = 1;
            break;
        }
        dsset_join_set(dsset,edge->from, edge->to);
        lnode = lnode->next;
    }

    dsset_destr(&dsset);
    return res;
}

int compare_edges(void *data_1, void *data_2)
{
    Edge *edge_1 = data_1, *edge_2 = data_2;
    if (edge_1->index > edge_2->index)
        return 1;
    else if (edge_1->index < edge_2->index)
        return -1;
    else
        return 0;
}

void print_egdes(void *data)
{
    Edge *edge = data;
    printf("%d -> (%d,%d)\n", edge->index, edge->from, edge->to);
}

void graphedg_print_edges(Graph *graphedge)
{
    list_print(graphedge->edges);
}

void graphedg_add_edges(Graph *graphedge, Edge *edge)
{
    list_insert(graphedge->edges, edge);
}

void print_set_vertex(DSNode *node)
{
    printf("%d ", node->index);
}